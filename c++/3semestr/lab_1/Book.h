#ifndef BOOK_H
#define BOOK_H

#include <cstring>

class Book {
private:
    // Указатель на строку для хранения названия книги
    char *title;
    // Количество страниц книги
    int pages;
    // Тираж книги
    int circulation;

    // Приватная функция для копирования строки в динамическую память
    char *copyString(const char *str);

public:
    // Конструктор по умолчанию
    Book();

    // Конструктор с параметрами для инициализации книги
    Book(const char *title, int pages, int circulation);

    // Конструктор копирования
    Book(const Book &other);

    // Оператор присваивания
    Book &operator=(const Book &other);

    // Оператор сложения для комбинирования двух книг
    Book operator+(const Book &other) const;

    // Функция для изменения данных книги
    void setBook(const char *title, int pages, int circulation);

    // Функция для отображения информации о книге
    void display() const;

    // Деструктор для освобождения динамически выделенной памяти
    ~Book();
};

#endif // BOOK_H