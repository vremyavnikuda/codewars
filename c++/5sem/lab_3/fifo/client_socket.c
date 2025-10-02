#include <dirent.h>
#include <errno.h>
#include <fcntl.h>
#include <pwd.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>

#define SOCKET_PATH "/tmp/tree_socket"
#define MAX_PATH 4096

// Глобальные переменные
int server_pid = 0;

// Рекурсивное сканирование директории
void scan_directory(int socket_fd, const char *path, int level, int max_depth)
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
            write(socket_fd, message, strlen(message));
            // Рекурсивно сканируем поддиректорию
            scan_directory(socket_fd, full_path, level + 1, max_depth);
        }
        else if (S_ISREG(statbuf.st_mode))
        {
            // Это обычный файл
            snprintf(message, MAX_PATH, "F:%d:%s\n", level, entry->d_name);
            write(socket_fd, message, strlen(message));
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
    int socket_fd;
    struct sockaddr_un addr;
    // Ограничиваем глубину сканирования по умолчанию
    int max_depth = 3;
    printf("Tree Client Started (Sockets)\n");
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
    // Создание сокета
    if ((socket_fd = socket(AF_UNIX, SOCK_STREAM, 0)) == -1)
    {
        perror("socket");
        exit(1);
    }
    // Настройка адреса сокета
    memset(&addr, 0, sizeof(addr));
    addr.sun_family = AF_UNIX;
    strncpy(addr.sun_path, SOCKET_PATH, sizeof(addr.sun_path) - 1);
    // Подключение к серверу
    printf("Connecting to server...\n");
    if (connect(socket_fd, (struct sockaddr *)&addr, sizeof(addr)) == -1)
    {
        perror("connect");
        close(socket_fd);
        exit(1);
    }
    printf("Connected!\n");
    printf("Scanning directories...\n\n");
    // Отправляем корневую директорию
    char message[MAX_PATH];
    snprintf(message, MAX_PATH, "D:0:%s\n", home_dir);
    write(socket_fd, message, strlen(message));
    // Сканируем дерево директорий
    scan_directory(socket_fd, home_dir, 1, max_depth);
    printf("Scanning completed!\n");
    printf("Data sent to server.\n");
    // Небольшая пауза для гарантии передачи всех данных
    usleep(100000);
    // Закрываем сокет
    close(socket_fd);
    // Уведомляем сервер о завершении
    kill(server_pid, SIGUSR2);
    printf("Client shutting down...\n");
    return 0;
}