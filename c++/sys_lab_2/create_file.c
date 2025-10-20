#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>

int main(int argc, char *argv[]) {
    // Проверка, передано ли правильное количество аргументов
    if (argc != 3) {
        fprintf(stderr, "Использование: %s <имя_файла> <содержимое>\n", argv[0]);
        return 1;
    }

    const char *filename = argv[1];
    const char *content = argv[2];
    int fd;

    // Используем системный вызов open для создания файла
    fd = open(filename, O_CREAT | O_WRONLY | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
    
    if (fd == -1) {
        perror("Ошибка при создании файла");
        return 1;
    }

    // Используем системный вызов write для записи содержимого в файл
    ssize_t bytes_written = write(fd, content, strlen(content));
    
    if (bytes_written == -1) {
        perror("Ошибка при записи в файл");
        close(fd);
        return 1;
    }

    // Закрываем файловый дескриптор
    close(fd);

    printf("Файл '%s' успешно создан с содержимым: %s\n", filename, content);
    return 0;
}