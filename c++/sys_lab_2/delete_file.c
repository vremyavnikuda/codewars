#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    // Проверка, передано ли правильное количество аргументов
    if (argc != 2) {
        fprintf(stderr, "Использование: %s <имя_файла>\n", argv[0]);
        return 1;
    }

    const char *filename = argv[1];

    // Используем системный вызов unlink для удаления файла
    if (unlink(filename) == -1) {
        perror("Ошибка при удалении файла");
        return 1;
    }

    printf("Файл '%s' успешно удалён\n", filename);
    return 0;
}