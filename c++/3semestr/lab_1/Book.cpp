#include "Book.h"
#include <iostream>

// Конструктор по умолчанию, инициализирует title как nullptr, pages и circulation как 0
Book::Book() : title(nullptr), pages(0), circulation(0) {
}

// Конструктор с параметрами, инициализирует title, pages и circulation
Book::Book(const char *title, int pages, int circulation) : pages(pages), circulation(circulation) {
    // Копирует строку title
    this->title = copyString(title);
}

// Конструктор копирования, создает копию другой книги
Book::Book(const Book &other) : pages(other.pages), circulation(other.circulation) {
    // Копирует title из другой книги
    title = copyString(other.title);
}

// Оператор присваивания, копирует данные одной книги в другую
Book &Book::operator=(const Book &other) {
    if (this == &other) {
        // Если объект сам себе присваивается, возвращаем себя
        return *this;
    }
    // Освобождаем память, занятую текущим title
    delete[] title;
    // Копируем title из другой книги
    title = copyString(other.title);
    // Копируем количество страниц
    pages = other.pages;
    // Копируем тираж
    circulation = other.circulation;
    return *this;
}

// Оператор сложения, объединяет две книги в одну
Book Book::operator+(const Book &other) const {
    // Используем title текущей книги или пустую строку
    const char *thisTitle = this->title ? this->title : "";
    // Используем title другой книги или пустую строку
    const char *otherTitle = other.title ? other.title : "";
    // Длина нового названия с " & "
    size_t newTitleLen = strlen(thisTitle) + strlen(otherTitle) + 4;
    // Выделяем память для нового названия
    char *newTitle = new char[newTitleLen];
    // Копируем название текущей книги
    strcpy(newTitle, thisTitle);
    // Добавляем " & "
    strcat(newTitle, " & ");
    // Добавляем название другой книги
    strcat(newTitle, otherTitle);
    // Создаем новую книгу с объединенными данными
    Book newBook(newTitle, this->pages + other.pages, this->circulation + other.circulation);
    // Освобождаем память, выделенную для нового названия
    delete[] newTitle;
    return newBook;
}

// Функция для изменения данных книги
void Book::setBook(const char *title, int pages, int circulation) {
    // Освобождаем память, занятую текущим title
    delete[] this->title;
    // Копируем новое название
    this->title = copyString(title);
    // Устанавливаем новое количество страниц
    this->pages = pages;
    // Устанавливаем новый тираж
    this->circulation = circulation;
}

// Функция для вывода информации о книге
void Book::display() const {
    // Выводим название или "Unknown" если title nullptr
    std::cout << "Title: " << (title ? title : "Unknown") << std::endl;
    // Выводим количество страниц
    std::cout << "Pages: " << pages << std::endl;
    // Выводим тираж
    std::cout << "Circulation: " << circulation << std::endl;
}

// Деструктор, освобождает память, выделенную для title
Book::~Book() {
    delete[] title;
}

// Внутренняя функция для копирования строк
char *Book::copyString(const char *str) {
    if (str == nullptr) {
        // Возвращаем nullptr если str nullptr
        return nullptr;
    }
    // Выделяем память для новой строки
    char *newStr = new char[strlen(str) + 1];
    // Копируем строку
    strcpy(newStr, str);
    return newStr;
}
