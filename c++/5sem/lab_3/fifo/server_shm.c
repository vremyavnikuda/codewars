#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <signal.h>
#include <errno.h>

#define SHM_KEY 0x1234
#define BUFFER_SIZE 4096

// Структура для разделяемой памяти
typedef struct {
    char data[BUFFER_SIZE];
    // Флаг готовности данных
    int ready;      
    // Флаг завершения
    int done;       
} shared_data_t;

// Глобальные переменные
shared_data_t *shm_ptr = NULL;
int shmid = -1;

// Функция очистки разделяемой памяти
void cleanup_shm() {
    if (shm_ptr) {
        shmdt(shm_ptr);
    }
    if (shmid != -1) {
        shmctl(shmid, IPC_RMID, NULL);
    }
}

// Функция для вывода дерева с красивым форматированием
void print_tree_line(int level, const char *name, char type) {
    // Рисуем отступы и символы дерева
    for (int i = 0; i < level; i++) {
        if (i == level - 1) {
            printf("├── ");
        } else {
            printf("│   ");
        }
    }
    if (type == 'D') {
        // Директории синим цветом
        printf("\033[1;34m%s/\033[0m\n", name);
    } else {
        // Файлы обычным цветом
        printf("%s\n", name);
    }
}

int main() {
    printf("Tree Server Started (Shared Memory)\n");
    // Создание разделяемой памяти
    shmid = shmget(SHM_KEY, sizeof(shared_data_t), IPC_CREAT | 0666);
    if (shmid == -1) {
        perror("shmget");
        exit(1);
    }
    // Подключение к разделяемой памяти
    shm_ptr = (shared_data_t*)shmat(shmid, NULL, 0);
    if (shm_ptr == (void*)-1) {
        perror("shmat");
        cleanup_shm();
        exit(1);
    }
    // Инициализация разделяемых данных
    shm_ptr->ready = 0;
    shm_ptr->done = 0;
    printf("Shared memory created with ID: %d\n", shmid);
    printf("Server PID: %d\n\n", getpid());
    printf("Waiting for client data...\n\n");
    printf("Directory Tree:\n");
    printf("###################################\n");
    // Ожидание и обработка данных от клиента
    char leftover[BUFFER_SIZE] = "";
    while (!shm_ptr->done) {
        if (shm_ptr->ready) {
            // Данные готовы, обрабатываем их
            char combined[BUFFER_SIZE * 2];
            snprintf(combined, sizeof(combined), "%s%s", leftover, shm_ptr->data);
            // Обрабатываем построчно
            char *line = strtok(combined, "\n");
            char *last_line = NULL;
            while (line != NULL) {
                last_line = line;
                // Парсим строку: тип:уровень:имя
                char type;
                int level;
                char name[512];
                if (sscanf(line, "%c:%d:%511[^\n]", &type, &level, name) == 3) {
                    print_tree_line(level, name, type);
                }
                line = strtok(NULL, "\n");
            }
            // Сохраняем неполную строку для следующей итерации
            if (last_line != NULL && combined[strlen(combined) - 1] != '\n') {
                strcpy(leftover, last_line);
            } else {
                leftover[0] = '\0';
            }
            // Сбрасываем флаг готовности
            shm_ptr->ready = 0;
        }
        // Краткая задержка, чтобы не перегружать процессор
        usleep(10000);
    }
    printf("###################################\n");
    printf("\nTree display completed!\n");
    // Отключение от разделяемой памяти
    cleanup_shm();
    printf("Server shutting down...\n");
    return 0;
}