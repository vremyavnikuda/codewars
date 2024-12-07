#ifndef BOOK_H
#define BOOK_H

#include <fstream>

class Book {
private:
    // Указатель на строку, хранящую название книги
    char *title;
    // Количество страниц в книге
    int pages;
    // Тираж книги
    int circulation;

    // Функция для копирования строки
    char *copyString(const char *str);

public:
    // Конструкторы
    Book(); // Конструктор по умолчанию
    // Конструктор с параметрами
    Book(const char *title, int pages, int circulation);
    // Конструктор копирования
    Book(const Book &other);

    // Деструктор
    ~Book(); // Деструктор для освобождения памяти

    // Оператор присваивания
    // Оператор присваивания (копирования)
    Book &operator=(const Book &other);

    // Операторы перегрузки
    // Оператор сложения (для объединения книг)
    Book operator+(const Book &other) const;
    // Оператор вычитания (для разности книг)
    friend Book operator-(const Book &lhs, const Book &rhs);
    // Префиксный инкремент (увеличение количества страниц и тиража)
    Book &operator++();
    // Постфиксный инкремент (увеличение количества страниц и тиража, но возвращаем старое значение)
    Book operator++(int);
    // Преобразование объекта книги в int (сумма страниц и тиража)
    operator int() const;

    // Операторы ввода/вывода
    // Оператор вывода (для печати книги в поток)
    friend std::ostream &operator<<(std::ostream &os, const Book &book);
    // Оператор ввода (для чтения книги из потока)
    friend std::istream &operator>>(std::istream &is, Book &book);

    // Функции для работы с файлами
    // Сохранить книгу в бинарный файл
    void saveToBinaryFile(const char *filename) const;
    // Загрузить книгу из бинарного файла
    void loadFromBinaryFile(const char *filename);

    // Прочие методы
    // Устанавливаем данные книги
    void setBook(const char *title, int pages, int circulation);
    // Информацию о книге
    void display() const;
};

#endif // BOOK_H
