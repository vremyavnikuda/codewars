#include <dirent.h>
#include <errno.h>
#include <fcntl.h>
#include <pwd.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

#define FIFO_NAME "/tmp/tree_fifo_new"
#define MAX_PATH 4096

int server_pid = 0;
int fifo_fd = -1;

// Рекурсивное сканирование директории
void scan_directory(int fd, const char *path, int level, int max_depth) {
  DIR *dir;
  struct dirent *entry;
  struct stat statbuf;
  char full_path[MAX_PATH];
  char message[MAX_PATH];
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
      write(fd, message, strlen(message));
      // Рекурсивно сканируем поддиректорию
      scan_directory(fd, full_path, level + 1, max_depth);
    } else if (S_ISREG(statbuf.st_mode)) {
      // Это обычный файл
      snprintf(message, MAX_PATH, "F:%d:%s\n", level, entry->d_name);
      write(fd, message, strlen(message));
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
  // Ограничиваем глубину сканирования по умолчанию
  int max_depth = 3;
  printf("Tree Client Started (Named Pipes)\n");
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
  // Ждем, пока сервер создаст FIFO
  printf("Waiting for server...\n");
  for (int i = 0; i < 10; i++) {
    if (access(FIFO_NAME, F_OK) == 0) {
      break;
    }
    sleep(1);
  }
  if (access(FIFO_NAME, F_OK) != 0) {
    fprintf(stderr, "Error: Server not found. Start server first!\n");
    exit(1);
  }
  // Открываем канал для записи
  printf("Connecting to server...\n");
  fifo_fd = open(FIFO_NAME, O_WRONLY);
  if (fifo_fd == -1) {
    perror("open");
    exit(1);
  }
  printf("Connected!\n");
  printf("Scanning directories...\n\n");
  // Отправляем корневую директорию
  char message[MAX_PATH];
  snprintf(message, MAX_PATH, "D:0:%s\n", home_dir);
  write(fifo_fd, message, strlen(message));
  // Сканируем дерево директорий
  scan_directory(fifo_fd, home_dir, 1, max_depth);
  printf("Scanning completed!\n");
  printf("Data sent to server.\n");
  // Небольшая пауза для гарантии передачи всех данных
  usleep(100000);
  // Закрываем канал
  close(fifo_fd);
  printf("Client shutting down...\n");
  return 0;
}