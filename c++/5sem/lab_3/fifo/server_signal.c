#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>
#include <errno.h>

#define MAX_PATH 4096
#define BUFFER_SIZE 4096

// Глобальные переменные для обработки сигналов
volatile sig_atomic_t data_ready = 0;
volatile sig_atomic_t client_done = 0;
char shared_buffer[BUFFER_SIZE];
pid_t client_pid = 0;

// Обработчик сигналов
void signal_handler(int signum) {
    if (signum == SIGUSR1) {
        data_ready = 1;
    } else if (signum == SIGUSR2) {
        client_done = 1;
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
    printf("Tree Server Started (Signals)\n");
    // Установка обработчиков сигналов
    signal(SIGUSR1, signal_handler);
    signal(SIGUSR2, signal_handler);
    printf("Server PID: %d\n\n", getpid());
    printf("Waiting for client connection...\n\n");
    // Ожидание сигнала от клиента о подключении
    while (client_pid == 0) {
        sleep(1);
    }
    printf("Client connected!\n");
    printf("Receiving directory tree...\n\n");
    printf("Directory Tree:\n");
    printf("###################################\n");
    // Ожидание и обработка данных от клиента
    char leftover[BUFFER_SIZE] = "";
    while (!client_done) {
        if (data_ready) {
            // Обрабатываем данные из буфера
            char combined[BUFFER_SIZE * 2];
            snprintf(combined, sizeof(combined), "%s%s", leftover, shared_buffer);
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
            // Сбрасываем флаг
            data_ready = 0;
            // Отправляем сигнал клиенту, что данные обработаны
            if (client_pid > 0) {
                kill(client_pid, SIGUSR1);
            }
        }
        // Краткая задержка, чтобы не перегружать процессор
        usleep(10000);
    }
    printf("###################################\n");
    printf("\nTree display completed!\n");
    printf("Server shutting down...\n");
    return 0;
}