#include <dirent.h>
#include <errno.h>
#include <fcntl.h>
#include <pwd.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/sem.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>

#define SEM_KEY 0x5678
#define SHM_KEY 0x1234
#define BUFFER_SIZE 4096
#define MAX_PATH 4096

// Union для работы с семафорами
union semun {
    int val;
    struct semid_ds *buf;
    unsigned short *array;
};

// Структура для разделяемой памяти
typedef struct {
    char data[BUFFER_SIZE];
    // Флаг завершения
    int done;       
} shared_data_t;

// Глобальные переменные
shared_data_t *shm_ptr = NULL;
int server_pid = 0;
int shmid = -1;
int semid = -1;
// Индексы семафоров
int sem_empty, sem_full;

// Рекурсивное сканирование директории
void scan_directory_sem(const char *path, int level, int max_depth) {
    DIR *dir;
    struct dirent *entry;
    struct stat statbuf;
    char full_path[MAX_PATH];
    char message[MAX_PATH];
    struct sembuf sop;
    // Ограничение глубины рекурсии
    if (level > max_depth) {
        return;
    }
    dir = opendir(path);
    if (dir == NULL) {
        // Нет прав доступа или другая ошибка
        return;
    }
    while ((entry = readdir(dir)) != NULL) {
        // Пропускаем . и ..
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
            continue;
        }
        // Создаем полный путь
        snprintf(full_path, MAX_PATH, "%s/%s", path, entry->d_name);
        // Получаем информацию о файле
        if (lstat(full_path, &statbuf) == -1) {
            continue;
        }
        // Формируем и отправляем сообщение
        if (S_ISDIR(statbuf.st_mode)) {
            // Это директория
            snprintf(message, MAX_PATH, "D:%d:%s\n", level, entry->d_name);
            // Ждем, пока буфер не будет пуст
            sop.sem_num = sem_empty;
            sop.sem_op = -1;  // Уменьшаем семафор (ждет, если 0)
            sop.sem_flg = 0;
            if (semop(semid, &sop, 1) == -1) {
                perror("semop wait empty");
                closedir(dir);
                return;
            }
            // Копируем сообщение в разделяемую память
            strncpy(shm_ptr->data, message, MAX_PATH);
            shm_ptr->data[MAX_PATH-1] = '\0';
            // Сигнализируем, что буфер заполнен
            sop.sem_num = sem_full;
            sop.sem_op = 1;  // Увеличиваем семафор (буфер полон)
            sop.sem_flg = 0;
            if (semop(semid, &sop, 1) == -1) {
                perror("semop signal full");
                closedir(dir);
                return;
            }
            // Рекурсивно сканируем поддиректорию
            scan_directory_sem(full_path, level + 1, max_depth);
        } else if (S_ISREG(statbuf.st_mode)) {
            // Это обычный файл
            snprintf(message, MAX_PATH, "F:%d:%s\n", level, entry->d_name);
            // Ждем, пока буфер не будет пуст
            sop.sem_num = sem_empty;
            // Уменьшаем семафор (ждет, если 0)
            sop.sem_op = -1;
            sop.sem_flg = 0;
            if (semop(semid, &sop, 1) == -1) {
                perror("semop wait empty");
                closedir(dir);
                return;
            }
            // Копируем сообщение в разделяемую память
            strncpy(shm_ptr->data, message, MAX_PATH);
            shm_ptr->data[MAX_PATH-1] = '\0';
            // Сигнализируем, что буфер заполнен
            sop.sem_num = sem_full;
            // Увеличиваем семафор (буфер полон)
            sop.sem_op = 1;
            sop.sem_flg = 0;
            if (semop(semid, &sop, 1) == -1) {
                perror("semop signal full");
                closedir(dir);
                return;
            }
        }
    }
    closedir(dir);
}

// Функция для получения домашней директории
char *get_home_directory() {
    char *home = getenv("HOME");
    if (home != NULL) {
        return home;
    }
    // Альтернативный способ через passwd
    struct passwd *pw = getpwuid(getuid());
    if (pw != NULL) {
        return pw->pw_dir;
    }
    return NULL;
}

int main(int argc, char *argv[]) {
    char *home_dir;
    struct sembuf sop;
    // Ограничиваем глубину сканирования по умолчанию
    int max_depth = 3;
    printf("Tree Client Started (Semaphores)\n");
    // Обработка аргументов командной строки
    if (argc > 1) {
        max_depth = atoi(argv[1]);
        if (max_depth < 1 || max_depth > 10) {
            fprintf(stderr, "Invalid depth. Using default: 3\n");
            max_depth = 3;
        }
    }
    // Получаем домашнюю директорию
    home_dir = get_home_directory();
    if (home_dir == NULL) {
        fprintf(stderr, "Error: Cannot determine home directory\n");
        exit(1);
    }
    printf("Home directory: %s\n", home_dir);
    printf("Scan depth: %d levels\n", max_depth);
    // Получение доступа к разделяемой памяти
    shmid = shmget(SHM_KEY, sizeof(shared_data_t), 0666);
    if (shmid == -1) {
        perror("shmget - client");
        exit(1);
    }
    // Подключение к разделяемой памяти
    shm_ptr = (shared_data_t*)shmat(shmid, NULL, 0);
    if (shm_ptr == (void*)-1) {
        perror("shmat");
        exit(1);
    }
    // Получение доступа к семафорам
    semid = semget(SEM_KEY, 2, 0666);
    if (semid == -1) {
        perror("semget - client");
        shmdt(shm_ptr);
        exit(1);
    }
    sem_empty = 0;
    sem_full = 1;
    printf("Connected to shared memory and semaphores!\n");
    printf("Scanning directories...\n\n");
    // Ждем, пока буфер не будет пуст
    sop.sem_num = sem_empty;
    // Уменьшаем семафор (ждет, если 0)
    sop.sem_op = -1;
    sop.sem_flg = 0;
    if (semop(semid, &sop, 1) == -1) {
        perror("semop wait empty");
        shmdt(shm_ptr);
        return 1;
    }
    // Отправляем корневую директорию
    char message[MAX_PATH];
    snprintf(message, MAX_PATH, "D:0:%s\n", home_dir);
    // Копируем сообщение в разделяемую память
    strncpy(shm_ptr->data, message, MAX_PATH);
    shm_ptr->data[MAX_PATH-1] = '\0';
    // Сигнализируем, что буфер заполнен
    sop.sem_num = sem_full;
    // Увеличиваем семафор (буфер полон)
    sop.sem_op = 1;
    sop.sem_flg = 0;
    if (semop(semid, &sop, 1) == -1) {
        perror("semop signal full");
        shmdt(shm_ptr);
        return 1;
    }
    // Сканируем дерево директорий
    scan_directory_sem(home_dir, 1, max_depth);
    printf("Scanning completed!\n");
    printf("Data sent to server.\n");
    // Устанавливаем флаг завершения
    // Ждем, пока буфер не будет пуст
    sop.sem_num = sem_empty;
    // Уменьшаем семафор (ждет, если 0)
    sop.sem_op = -1;
    sop.sem_flg = 0;
    if (semop(semid, &sop, 1) == -1) {
        perror("semop wait empty for done");
    } else {
        shm_ptr->done = 1;
        // Сигнализируем, что буфер заполнен
        sop.sem_num = sem_full;
        // Увеличиваем семафор (буфер полон)
        sop.sem_op = 1;
        sop.sem_flg = 0;
        if (semop(semid, &sop, 1) == -1) {
            perror("semop signal full for done");
        }
    }
    // Краткая пауза для гарантии передачи всех данных
    usleep(100000);
    // Отключение от разделяемой памяти
    shmdt(shm_ptr);
    printf("Client shutting down...\n");
    return 0;
}