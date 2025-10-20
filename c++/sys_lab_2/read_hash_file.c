#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

// Простая хеш-функция (алгоритм djb2)
unsigned long hash(unsigned char *str) {
    unsigned long hash = 5381;
    int c;

    while ((c = *str++))
        hash = ((hash << 5) + hash) + c;

    return hash;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Использование: %s <имя_файла>\n", argv[0]);
        return 1;
    }

    const char *filename = argv[1];
    int fd;
    char buffer[1024];
    ssize_t bytes_read;
    char *content = NULL;
    size_t total_size = 0;
    size_t allocated_size = 0;

    // Используем системный вызов open для открытия файла
    fd = open(filename, O_RDONLY);
    if (fd == -1) {
        perror("Ошибка при открытии файла");
        return 1;
    }

    // Читаем содержимое файла с помощью системного вызова read
    while ((bytes_read = read(fd, buffer, sizeof(buffer))) > 0) {
        // При необходимости увеличиваем размер буфера content
        if (total_size + bytes_read >= allocated_size) {
            allocated_size = allocated_size == 0 ? 1024 : allocated_size * 2;
            content = realloc(content, allocated_size);
            if (content == NULL) {
                fprintf(stderr, "Ошибка выделения памяти\n");
                close(fd);
                return 1;
            }
        }
        
        memcpy(content + total_size, buffer, bytes_read);
        total_size += bytes_read;
    }

    if (bytes_read == -1) {
        perror("Ошибка при чтении файла");
        free(content);
        close(fd);
        return 1;
    }

    close(fd);

    if (content != NULL) {
        // Добавляем завершающий нулевой символ
        if (total_size + 1 >= allocated_size) {
            content = realloc(content, total_size + 1);
        }
        content[total_size] = '\0';

        // Вычисляем хеш
        unsigned long file_hash = hash((unsigned char*)content);

        // Выводим имя файла и значение хеша
        printf("Имя файла: %s\n", filename);
        printf("Хеш: %lu\n", file_hash);
        printf("Содержимое:\n%s\n", content);

        free(content);
    } else {
        // Файл пустой
        unsigned long empty_hash = hash((unsigned char*)"");
        printf("Имя файла: %s\n", filename);
        printf("Хеш: %lu\n", empty_hash);
        printf("Содержимое: (пустой файл)\n");
    }

    return 0;
}