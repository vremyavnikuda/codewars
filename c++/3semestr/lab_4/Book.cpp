#include "Book.h"
#include <cstring>
#include <fstream>

// Конструктор по умолчанию инициализирует title как nullptr и pages и circulation как 0.
Book::Book() : title(nullptr), pages(0), circulation(0) {
}

// Конструктор, инициализирующий книгу с заданным названием, количеством страниц и тиражом.
Book::Book(const char *t, int p, int c) : pages(p), circulation(c) {
    title = copyString(t); // Безопасно копирует строку названия.
}

// Конструктор копирования, создаем копию другой книги.
Book::Book(const Book &other) : pages(other.pages), circulation(other.circulation) {
    title = copyString(other.title);
}

// Деструктор, освобождающий память, выделенную для title.
Book::~Book() {
    delete[] title;
}

// Оператор присваивания, копируем данные из другой книги.
Book &Book::operator=(const Book &other) {
    if (this != &other) {
        delete[] title;
        title = copyString(other.title);
        pages = other.pages;
        circulation = other.circulation;
    }
    return *this;
}

// Перегруженный оператор +, объединяющий две книги в новую.
Book Book::operator+(const Book &other) const {
    const char *thisTitle = this->title ? this->title : "";
    const char *otherTitle = other.title ? other.title : "";

    size_t newTitleLen = strlen(thisTitle) + strlen(otherTitle) + 4;
    char *newTitle = new char[newTitleLen];
    strcpy(newTitle, thisTitle);
    strcat(newTitle, " & ");
    strcat(newTitle, otherTitle);

    Book tempBook(newTitle, this->pages + other.pages, this->circulation + other.circulation);
    delete[] newTitle;
    return tempBook;
}

// Дружественная функция, вычисляющая разницу между книгами.
Book operator-(const Book &lhs, const Book &rhs) {
    const char *newTitle = "Difference";
    int newPages = lhs.pages - rhs.pages;
    int newCirculation = lhs.circulation - rhs.circulation;
    return Book(newTitle, newPages, newCirculation);
}

// Префиксный оператор инкремента, увеличивающий количество страниц и тираж на 1.
Book &Book::operator++() {
    ++pages;
    ++circulation;
    return *this;
}

// Постфиксный оператор инкремента, возвращающий старое состояние объекта перед инкрементом.
Book Book::operator++(int) {
    Book temp(*this);
    ++pages;
    ++circulation;
    return temp;
}

// Оператор преобразования в int, возвращающий сумму страниц и тиража.
Book::operator int() const {
    return pages + circulation;
}

// Установка данных книги, обновляющая название, количество страниц и тираж.
void Book::setBook(const char *title, int pages, int circulation) {
    delete[] this->title; // Освобождает текущее название.
    this->title = copyString(title); // Устанавливает новое название.
    this->pages = pages;
    this->circulation = circulation;
}

// Вывод информации о книге.
void Book::display() const {
    std::cout << "Title: " << (title ? title : "Unknown") << std::endl;
    std::cout << "Pages: " << pages << std::endl;
    std::cout << "Circulation: " << circulation << std::endl;
}

// Перегруженный оператор << вывод информации о книге в поток.
std::ostream &operator<<(std::ostream &os, const Book &book) {
    os << "Title: " << (book.title ? book.title : "Unknown") << "\n"
       << "Pages: " << book.pages << "\n"
       << "Circulation: " << book.circulation << "\n";
    return os;
}

// Перегруженный оператор >> ввода информации о книге из потока.
std::istream &operator>>(std::istream &is, Book &book) {
    char buffer[256];
    std::cout << "Enter title: ";
    is.ignore();
    is.getline(buffer, 256);
    book.title = book.copyString(buffer);

    std::cout << "Enter number of pages: ";
    is >> book.pages;

    std::cout << "Enter circulation: ";
    is >> book.circulation;
    return is;
}

// Сохранение данных книги в .bin
void Book::saveToBinaryFile(const char *filename) const {
    std::ofstream outFile(filename, std::ios::binary);
    if (!outFile.is_open()) {
        std::cerr << "Ошибка открытия файла для записи!" << std::endl;
        return;
    }
    size_t titleLength = strlen(title) + 1;
    outFile.write(reinterpret_cast<const char *>(&titleLength), sizeof(titleLength));
    outFile.write(title, titleLength);
    outFile.write(reinterpret_cast<const char *>(&pages), sizeof(pages));
    outFile.write(reinterpret_cast<const char *>(&circulation), sizeof(circulation));
    outFile.close();
}

// Загрузка данных книги из .bin.
void Book::loadFromBinaryFile(const char *filename) {
    std::ifstream inFile(filename, std::ios::binary);
    if (!inFile.is_open()) {
        std::cerr << "Ошибка открытия файла для чтения!" << std::endl;
        return;
    }
    size_t titleLength;
    inFile.read(reinterpret_cast<char *>(&titleLength), sizeof(titleLength));
    delete[] title;
    title = new char[titleLength];
    inFile.read(title, titleLength);
    inFile.read(reinterpret_cast<char *>(&pages), sizeof(pages));
    inFile.read(reinterpret_cast<char *>(&circulation), sizeof(circulation));
    inFile.close();
}

// Сохранение данных книги в .txt
void Book::saveToTextFile(const char *filename) const {
    std::ofstream outFile(filename);
    if (!outFile.is_open()) {
        std::cerr << "Ошибка открытия файла для записи!" << std::endl;
        return;
    }
    outFile << "Title: " << (title ? title : "Unknown") << std::endl;
    outFile << "Pages: " << pages << std::endl;
    outFile << "Circulation: " << circulation << std::endl;
    outFile.close();
}

// Вспомогательная функция для безопасного копирования C-строки, обрабатывающая nullptr.
char *Book::copyString(const char *str) {
    if (str == nullptr) return nullptr;
    size_t len = strlen(str) + 1;
    char *newStr = new char[len];
    strcpy(newStr, str);
    return newStr;
}