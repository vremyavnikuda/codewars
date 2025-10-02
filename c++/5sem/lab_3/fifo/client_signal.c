#include <dirent.h>
#include <errno.h>
#include <fcntl.h>
#include <pwd.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>

#define MAX_PATH 4096
#define BUFFER_SIZE 4096
#define SHM_KEY 0x5555

// Структура для разделяемой памяти
typedef struct
{
    char data[BUFFER_SIZE];
    // Флаг готовности данных
    int ready;
    // Флаг завершения
    int done;
} shared_data_t;

// Глобальные переменные
volatile sig_atomic_t server_ack = 0;
pid_t server_pid = 0;
shared_data_t *shm_ptr = NULL;
int shmid = -1;

// Обработчик сигналов
void signal_handler(int signum)
{
    if (signum == SIGUSR1)
    {
        server_ack = 1;
    }
}

// Рекурсивное сканирование директории
void scan_directory_signal(const char *path, int level, int max_depth)
{
    DIR *dir;
    struct dirent *entry;
    struct stat statbuf;
    char full_path[MAX_PATH];
    char message[MAX_PATH];
    // Ограничение глубины рекурсии
    if (level > max_depth)
    {
        return;
    }
    dir = opendir(path);
    if (dir == NULL)
    {
        // Нет прав доступа или другая ошибка
        return;
    }
    while ((entry = readdir(dir)) != NULL)
    {
        // Пропускаем . и ..
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
        {
            continue;
        }
        // Создаем полный путь
        snprintf(full_path, MAX_PATH, "%s/%s", path, entry->d_name);
        // Получаем информацию о файле
        if (lstat(full_path, &statbuf) == -1)
        {
            continue;
        }
        // Формируем и отправляем сообщение
        if (S_ISDIR(statbuf.st_mode))
        {
            // Это директория
            snprintf(message, MAX_PATH, "D:%d:%s\n", level, entry->d_name);
            // Копируем сообщение в разделяемую память
            strncpy(shm_ptr->data, message, MAX_PATH);
            shm_ptr->data[MAX_PATH - 1] = '\0';
            // Устанавливаем флаг готовности
            shm_ptr->ready = 1;
            // Отправляем сигнал серверу
            kill(server_pid, SIGUSR1);
            // Не ждем подтверждения от сервера, продолжаем
            usleep(5000); // Небольшая задержка для синхронизации
            // Рекурсивно сканируем поддиректорию
            scan_directory_signal(full_path, level + 1, max_depth);
        }
        else if (S_ISREG(statbuf.st_mode))
        {
            // Это обычный файл
            snprintf(message, MAX_PATH, "F:%d:%s\n", level, entry->d_name);
            // Копируем сообщение в разделяемую память
            strncpy(shm_ptr->data, message, MAX_PATH);
            shm_ptr->data[MAX_PATH - 1] = '\0';
            // Устанавливаем флаг готовности
            shm_ptr->ready = 1;
            // Отправляем сигнал серверу
            kill(server_pid, SIGUSR1);
            // Не ждем подтверждения от сервера, продолжаем
            // Небольшая задержка для синхронизации
            usleep(5000);
        }
    }
    closedir(dir);
}

// Функция для получения домашней директории
char *get_home_directory()
{
    char *home = getenv("HOME");
    if (home != NULL)
    {
        return home;
    }
    // Альтернативный способ через passwd
    struct passwd *pw = getpwuid(getuid());
    if (pw != NULL)
    {
        return pw->pw_dir;
    }
    return NULL;
}

int main(int argc, char *argv[])
{
    char *home_dir;
    // Ограничиваем глубину сканирования по умолчанию
    int max_depth = 3;
    printf("Tree Client Started (Signals with Shared Memory)\n");
    // Обработка аргументов командной строки
    if (argc > 1)
    {
        max_depth = atoi(argv[1]);
        if (max_depth < 1 || max_depth > 10)
        {
            fprintf(stderr, "Invalid depth. Using default: 3\n");
            max_depth = 3;
        }
    }
    // Получаем домашнюю директорию
    home_dir = get_home_directory();
    if (home_dir == NULL)
    {
        fprintf(stderr, "Error: Cannot determine home directory\n");
        exit(1);
    }
    printf("Home directory: %s\n", home_dir);
    printf("Scan depth: %d levels\n", max_depth);
    // Установка обработчика сигналов
    signal(SIGUSR1, signal_handler);
    // Получаем PID сервера (теперь нужно передавать как аргумент)
    if (argc < 3)
    {
        printf("Usage: %s <max_depth> <server_pid>\n", argv[0]);
        printf("Example: ./client_signal 3 <server_pid>\n");
        return 1;
    }
    server_pid = atoi(argv[2]);
    printf("Server PID: %d\n", server_pid);
    // Получение доступа к разделяемой памяти
    shmid = shmget(SHM_KEY, sizeof(shared_data_t), 0666);
    if (shmid == -1)
    {
        perror("shmget - client");
        exit(1);
    }
    // Подключение к разделяемой памяти
    shm_ptr = (shared_data_t *)shmat(shmid, NULL, 0);
    if (shm_ptr == (void *)-1)
    {
        perror("shmat");
        exit(1);
    }
    printf("Connected to shared memory!\n");
    printf("Scanning directories...\n\n");
    // Отправляем корневую директорию
    char message[MAX_PATH];
    snprintf(message, MAX_PATH, "D:0:%s\n", home_dir);
    // Копируем сообщение в разделяемую память
    strncpy(shm_ptr->data, message, MAX_PATH);
    shm_ptr->data[MAX_PATH - 1] = '\0';
    // Устанавливаем флаг готовности
    shm_ptr->ready = 1;
    // Отправляем сигнал серверу
    kill(server_pid, SIGUSR1);
    // Не ждем подтверждения от сервера, продолжаем
    // Небольшая задержка для синхронизации
    usleep(5000);
    // Сканируем дерево директорий
    scan_directory_signal(home_dir, 1, max_depth);
    printf("Scanning completed!\n");
    printf("Data sent to server.\n");
    // Устанавливаем флаг завершения
    shm_ptr->done = 1;
    // Отправляем сигнал о завершении
    kill(server_pid, SIGUSR2);
    // Краткая пауза для гарантии передачи всех данных
    usleep(100000);
    // Отключение от разделяемой памяти
    shmdt(shm_ptr);
    printf("Client shutting down...\n");
    return 0;
}