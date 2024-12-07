#include "Book.h"
#include <iostream>
#include <cstring>
#include <fstream>

// Вспомогательная функция для копирования строки
char *Book::copyString(const char *str) {
    // Если строка nullptr, возвращаю nullptr
    if (str == nullptr) return nullptr;

    // +1 для учета символа завершения строки
    size_t len = strlen(str) + 1;
    // Выделяем память для новой строки
    char *newStr = new char[len];
    // Копирую строку
    strcpy(newStr, str);
    // Возвращаю указатель на новую строку
    return newStr;
}

// Реализация конструктора по умолчанию
Book::Book() : title(nullptr), pages(0), circulation(0) {
}

// Конструктор с параметрами:
// инициализируем все члены класса
Book::Book(const char *title, int pages, int circulation) : pages(pages), circulation(circulation) {
    this->title = copyString(title); // Копируем строку с названием книги
}

// Конструктор копирования:
// создаем копию существующего объекта
Book::Book(const Book &other) : pages(other.pages), circulation(other.circulation) {
    // Копирую строку с названием книги
    title = copyString(other.title);
}

// Деструктор:
// освобождаем память, занятую строкой с названием книги
Book::~Book() {
    delete[] title;
}

// Оператор присваивания:
// освобождаем старую память и присваиваем новые значения
Book &Book::operator=(const Book &other) {
    if (this == &other) {
        // Если присваивает сам себе, ничего не делаем
        return *this;
    }
    // Освобождаю старую память
    delete[] title;
    // Копирую строку с названием книги
    title = copyString(other.title);
    // Копирую количество страниц
    this->pages = other.pages;
    // Копирую тираж
    this->circulation = other.circulation;
    // Возвращаю ссылку на текущий объект
    return *this;
}

// Оператор сложения (для объединения двух книг):
// комбинируем названия и суммируем данные
Book Book::operator+(const Book &other) const {
    // Если название есть, берем его, иначе пустую строку
    const char *thisTitle = this->title ? this->title : "";
    // То же самое для другой книги
    const char *otherTitle = other.title ? other.title : "";

    // 4 — это длина " & " между названиями
    size_t newTitleLen = strlen(thisTitle) + strlen(otherTitle) + 4;
    // Выделяю память для нового названия
    char *newTitle = new char[newTitleLen];
    // Копирую название первой книги
    strcpy(newTitle, thisTitle);
    // Добавим " & "
    strcat(newTitle, " & ");
    // Добавляю название второй книги
    strcat(newTitle, otherTitle);

    // Создаем новый объект книги с комбинированными данными
    Book tempBook(newTitle, this->pages + other.pages, this->circulation + other.circulation);
    // Освобождаю память для нового названия
    delete[] newTitle;

    // Возвращаем объединенную книгу
    return tempBook;
}

// Оператор вычитания (для разности двух книг): вычитаем страницы и тиражи
Book operator-(const Book &lhs, const Book &rhs) {
    // Название для книги-разности
    const char *newTitle = "Difference";
    // Разность страниц
    int newPages = lhs.pages - rhs.pages;
    // Разность тиражей
    int newCirculation = lhs.circulation - rhs.circulation;

    return Book(newTitle, newPages, newCirculation); // Возвращаем книгу-разность
}

// Префиксный инкремент (увеличиваем количество страниц и тиража)
Book &Book::operator++() {
    // Увеличиваю количество страниц
    ++pages;
    // Увеличиваю тираж
    ++circulation;
    // Возвращаем объект
    return *this;
}

// Постфиксный инкремент (сохраняем текущие значения и потом увеличиваем их)
Book Book::operator++(int) {
    // Создам временную копию текущего объекта
    Book temp(*this);
    // Увеличиваю количество страниц
    ++pages;
    // Увеличиваю тираж
    ++circulation;
    // Возвращаем копию объекта
    return temp;
}

// Преобразование в тип int: возвращаем сумму страниц и тиража
Book::operator int() const {
    // Возвращаем сумму страниц и тиража
    return pages + circulation;
}

// Метод для установки данных книги
void Book::setBook(const char *title, int pages, int circulation) {
    // Освобождаю старую память
    delete[] this->title;
    // Копирую новое название
    this->title = copyString(title);
    // Установим количество страниц
    this->pages = pages;
    // Установим тираж
    this->circulation = circulation;
}

// Метод для вывода данных о книге
void Book::display() const {
    // Название книги
    std::cout << "Title: " << (title ? title : "Unknown") << std::endl;
    // Количество страниц
    std::cout << "Pages: " << pages << std::endl;
    // Тираж
    std::cout << "Circulation: " << circulation << std::endl;
}

// Оператор вывода в поток (для вывода данных о книге в файл или на экран)
std::ostream &operator<<(std::ostream &os, const Book &book) {
    // Название книги
    os << "Title: " << (book.title ? book.title : "Unknown") << "\n"
            // Количество страниц
            << "Pages: " << book.pages << "\n"
            // Тираж
            << "Circulation: " << book.circulation << "\n";
    // Возвращаем result
    return os;
}

// Оператор ввода из потока (для ввода данных о книге с клавиатуры или из файла)
std::istream &operator>>(std::istream &is, Book &book) {
    // Буфер для ввода названия книги
    char buffer[256];
    // Название
    std::cout << "Enter title: ";
    // Пропускаем оставшийся символ новой строки после предыдущего ввода
    is.ignore();
    // Вводим название книги
    is.getline(buffer, 256);
    // Копируем введенную строку в поле title
    book.title = book.copyString(buffer);

    // Количество страниц
    std::cout << "Enter number of pages: ";
    // Количество страниц
    is >> book.pages;

    // Запрашиваем тираж
    std::cout << "Enter circulation: ";
    // Вводим тираж
    is >> book.circulation;

    // Возвращаем result операций
    return is;
}

// Метод для сохранения книги в бинарный файл
void Book::saveToBinaryFile(const char *filename) const {
    // Открываем файл для записи в бинарном формате
    std::ofstream outFile(filename, std::ios::binary);
    // Если не удается открыть файл, выводим ошибку и выходим
    if (!outFile.is_open()) {
        std::cerr << "Error opening file for writing!" << std::endl;
        return;
    }

    // Вычисляем длину названия книги
    size_t titleLength = strlen(title) + 1;
    // Записываем длину названия
    outFile.write(reinterpret_cast<const char *>(&titleLength), sizeof(titleLength));
    // Записываем само название
    outFile.write(title, titleLength);
    // Записываем количество страниц
    outFile.write(reinterpret_cast<const char *>(&pages), sizeof(pages));
    // Записываем тираж
    outFile.write(reinterpret_cast<const char *>(&circulation), sizeof(circulation));
    // Закрываем файл
    outFile.close();
}

// Метод для загрузки книги из бинарного файла
void Book::loadFromBinaryFile(const char *filename) {
    // Открываем файл для чтения в бинарном формате
    std::ifstream inFile(filename, std::ios::binary);
    // Если не удается открыть файл, выводим ошибку и выходим
    if (!inFile.is_open()) {
        std::cerr << "Error opening file for reading!" << std::endl;
        return;
    }

    size_t titleLength;
    // Читаем длину названия
    inFile.read(reinterpret_cast<char *>(&titleLength), sizeof(titleLength));
    // Освобождаем старую память для названия
    delete[] title;
    // Выделяем память для нового названия
    title = new char[titleLength];
    // Читаем название
    inFile.read(title, titleLength);
    // Читаем количество страниц
    inFile.read(reinterpret_cast<char *>(&pages), sizeof(pages));
    // Читаем тираж
    inFile.read(reinterpret_cast<char *>(&circulation), sizeof(circulation));
    // Закрываем файл
    inFile.close();
}
