#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <signal.h>
#include <errno.h>

#define SOCKET_PATH "/tmp/tree_socket"
#define BUFFER_SIZE 4096

// Глобальные переменные для обработки сигналов
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
    int server_fd, client_fd;
    struct sockaddr_un addr;
    char buffer[BUFFER_SIZE];
    char type;
    int level;
    char name[512];
    printf("Tree Server Started (Sockets)\n");
    printf("Creating socket...\n");
    // Установка обработчиков сигналов
    signal(SIGUSR2, signal_handler);
    // Создание UNIX сокета
    if ((server_fd = socket(AF_UNIX, SOCK_STREAM, 0)) == -1)
    {
        perror("socket");
        exit(1);
    }
    // Удаление старого сокета, если существует
    unlink(SOCKET_PATH);
    // Настройка адреса сокета
    memset(&addr, 0, sizeof(addr));
    addr.sun_family = AF_UNIX;
    strncpy(addr.sun_path, SOCKET_PATH, sizeof(addr.sun_path) - 1);
    // Привязка сокета
    if (bind(server_fd, (struct sockaddr *)&addr, sizeof(addr)) == -1)
    {
        perror("bind");
        close(server_fd);
        exit(1);
    }
    // Прослушивание
    if (listen(server_fd, 1) == -1)
    {
        perror("listen");
        close(server_fd);
        exit(1);
    }
    printf("Socket created: %s\n", SOCKET_PATH);
    printf("Server PID: %d\n\n", getpid());
    printf("Waiting for client connection...\n");
    // Принятие соединения
    client_fd = accept(server_fd, NULL, NULL);
    if (client_fd == -1)
    {
        perror("accept");
        close(server_fd);
        exit(1);
    }
    printf("Client connected!\n");
    printf("Receiving directory tree...\n\n");
    printf("Directory Tree:\n");
    printf("###################################\n");
    // Чтение данных из сокета
    ssize_t bytes_read;
    char leftover[BUFFER_SIZE] = "";
    while (!client_done)
    {
        bytes_read = read(client_fd, buffer, BUFFER_SIZE - 1);
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
            // Конец данных - клиент закрыл соединение
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
    printf("###################################\n");
    printf("\nTree display completed!\n");
    // Закрытие сокетов
    close(client_fd);
    close(server_fd);
    unlink(SOCKET_PATH);
    printf("Server shutting down...\n");
    return 0;
}