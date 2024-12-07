#ifndef FICTIONBOOK_H
#define FICTIONBOOK_H

#include "Book.h" // Включаем заголовочный файл базового класса Book

class FictionBook : public Book {
    // Класс FictionBook наследует от класса Book
private:
    char *author; // Указатель на строку с именем автора книги

public:
    // Конструктор по умолчанию для FictionBook
    FictionBook();

    // Конструктор инициализации с параметрами: название, количество страниц, тираж и автор
    FictionBook(const char *t, int p, int c, const char *a);

    // Конструктор копирования для FictionBook
    FictionBook(const FictionBook &other);

    // Виртуальный деструктор для освобождения памяти, выделенной для author
    virtual ~FictionBook();

    // Оператор присваивания для FictionBook
    FictionBook &operator=(const FictionBook &other);

    // Переопределенный метод для отображения информации о книге, включая автора
    void display() const override;

    // Переопределенный метод для сохранения данных книги в двоичный файл, включая автора
    void saveToBinaryFile(const char *filename) const override;

    // Переопределенный метод для загрузки данных книги из двоичного файла, включая автора
    void loadFromBinaryFile(const char *filename) override;

    // Переопределенный метод для сохранения данных книги в текстовый файл, включая авто
    void saveToTextFile(const char *filename) const override;
};

#endif // FICTIONBOOK_H
