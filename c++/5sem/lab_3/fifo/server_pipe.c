#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <signal.h>
#include <errno.h>

#define FIFO_NAME "/tmp/tree_fifo_new"
#define BUFFER_SIZE 4096

volatile sig_atomic_t client_done = 0;

// Обработчик сигналов
void signal_handler(int signum)
{
    if (signum == SIGUSR2)
    {
        client_done = 1;
    }
}

// Функция для вывода дерева с красивым форматированием
void print_tree_line(int level, const char *name, char type)
{
    // Рисуем отступы и символы дерева
    for (int i = 0; i < level; i++)
    {
        if (i == level - 1)
        {
            printf("├── ");
        }
        else
        {
            printf("│   ");
        }
    }
    if (type == 'D')
    {
        // Директории синим цветом
        printf("\033[1;34m%s/\033[0m\n", name);
    }
    else
    {
        // Файлы обычным цветом
        printf("%s\n", name);
    }
}

int main()
{
    int fd;
    char buffer[BUFFER_SIZE];
    char type;
    int level;
    char name[512];
    printf("Tree Server Started (Named Pipes)\n");
    printf("Waiting for client connection...\n\n");
    // Установка обработчиков сигналов
    signal(SIGUSR2, signal_handler);
    // Создание именованного канала
    // Удаляем старый канал, если существует
    unlink(FIFO_NAME);
    if (mkfifo(FIFO_NAME, 0666) == -1)
    {
        perror("mkfifo");
        exit(1);
    }
    printf("FIFO created: %s\n", FIFO_NAME);
    printf("Server PID: %d\n\n", getpid());
    // Открытие канала для чтения
    fd = open(FIFO_NAME, O_RDONLY);
    if (fd == -1)
    {
        perror("open");
        unlink(FIFO_NAME);
        exit(1);
    }
    printf("Client connected!\n");
    printf("Receiving directory tree...\n\n");
    printf("Directory Tree:\n");
    printf("#################################\n");

    // Чтение данных из канала
    ssize_t bytes_read;
    char leftover[BUFFER_SIZE] = "";
    while (!client_done)
    {
        bytes_read = read(fd, buffer, BUFFER_SIZE - 1);
        if (bytes_read > 0)
        {
            buffer[bytes_read] = '\0';
            // Объединяем с остатком предыдущего чтения
            char combined[BUFFER_SIZE * 2];
            snprintf(combined, sizeof(combined), "%s%s", leftover, buffer);
            // Обрабатываем построчно
            char *line = strtok(combined, "\n");
            char *last_line = NULL;
            while (line != NULL)
            {
                last_line = line;
                // Парсим строку: тип:уровень:имя
                if (sscanf(line, "%c:%d:%511[^\n]", &type, &level, name) == 3)
                {
                    print_tree_line(level, name, type);
                }
                line = strtok(NULL, "\n");
            }
            // Сохраняем неполную строку для следующей итерации
            if (last_line != NULL && combined[strlen(combined) - 1] != '\n')
            {
                strcpy(leftover, last_line);
            }
            else
            {
                leftover[0] = '\0';
            }
        }
        else if (bytes_read == 0)
        {
            // Конец файла - клиент закрыл канал
            break;
        }
        else
        {
            if (errno == EINTR)
            {
                // Прерывание сигналом - продолжаем
                continue;
            }
            perror("read");
            break;
        }
    }
    printf("#################################\n");
    printf("\nTree display completed!\n");
    // Закрытие и удаление канала
    close(fd);
    unlink(FIFO_NAME);
    printf("Server shutting down...\n");
    return 0;
}