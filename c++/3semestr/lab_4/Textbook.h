#ifndef TEXTBOOK_H
#define TEXTBOOK_H

#include "Book.h"

// Класс Textbook <- Book
class Textbook : public Book {
private:
    // Уровень образования, для которого предназначен учебник
    int level;

public:
    Textbook(); // Конструктор по умолчанию

    // Конструктор с параметрами: заголовок, цена, количество, уровень
    Textbook(const char *t, int p, int c, int l);

    // Конструктор копирования
    Textbook(const Textbook &other);

    // Конструктор с дополнительными параметрами
    Textbook(const char *str, int i, int i1, const char *text, int i2);

    // Виртуальный деструктор
    virtual ~Textbook();

    // Перегрузка оператора присваивания
    Textbook &operator=(const Textbook &other);

    // Виртуальная функция для отображения информации о учебнике
    void display() const override;

    // Сохраняет данные в бинарный файл
    void saveToBinaryFile(const char *filename) const override;

    // Загружает данные из бинарного файла
    void loadFromBinaryFile(const char *filename) override;

    // Сохраняет данные в текстовый файл
    void saveToTextFile(const char *filename) const override;
};

#endif // TEXTBOOK_H
