#include "FictionBook.h"
#include <cstring>
#include <fstream>

// Конструктор по умолчанию для FictionBook, инициализирует author как nullptr.
FictionBook::FictionBook() : Book(), author(nullptr) {
}

// Конструктор инициализации для FictionBook с параметрами.
FictionBook::FictionBook(const char *t, int p, int c, const char *a)
    : Book(t, p, c), author(copyString(a)) {
}

// Конструктор копирования для FictionBook.
FictionBook::FictionBook(const FictionBook &other)
    : Book(other), author(copyString(other.author)) {
}

// Деструктор для FictionBook, освобождающий память, выделенную для author.
FictionBook::~FictionBook() {
    delete[] author;
}

// Оператор присваивания для FictionBook.
FictionBook &FictionBook::operator=(const FictionBook &other) {
    if (this != &other) {
        Book::operator=(other);
        delete[] author;
        author = copyString(other.author);
    }
    return *this;
}

// Переопределенный метод display() для вывода информации о FictionBook.
void FictionBook::display() const {
    Book::display();
    std::cout << "Author: " << (author ? author : "Unknown") << std::endl; // Выводим автора.
}

// Переопределенный метод для сохранения данных FictionBook в .bin.
void FictionBook::saveToBinaryFile(const char *filename) const {
    std::ofstream outFile(filename, std::ios::binary);
    if (!outFile.is_open()) {
        std::cerr << "errorOpeningFileForWriting" << std::endl;
        return;
    }
    size_t titleLength = strlen(title) + 1;
    size_t authorLength = strlen(author) + 1;
    outFile.write(reinterpret_cast<const char *>(&titleLength), sizeof(titleLength));
    outFile.write(title, titleLength);
    outFile.write(reinterpret_cast<const char *>(&authorLength), sizeof(authorLength));
    outFile.write(author, authorLength);
    outFile.write(reinterpret_cast<const char *>(&pages), sizeof(pages));
    outFile.write(reinterpret_cast<const char *>(&circulation), sizeof(circulation));
    outFile.close();
}

// Переопределенный метод для загрузки данных FictionBook из .bin.
void FictionBook::loadFromBinaryFile(const char *filename) {
    std::ifstream inFile(filename, std::ios::binary);
    if (!inFile.is_open()) {
        std::cerr << "errorOpeningFileForReading" << std::endl;
        return;
    }
    size_t titleLength, authorLength;
    inFile.read(reinterpret_cast<char *>(&titleLength), sizeof(titleLength));
    delete[] title;
    title = new char[titleLength];
    inFile.read(title, titleLength);

    inFile.read(reinterpret_cast<char *>(&authorLength), sizeof(authorLength));
    delete[] author;
    author = new char[authorLength];
    inFile.read(author, authorLength);

    inFile.read(reinterpret_cast<char *>(&pages), sizeof(pages));
    inFile.read(reinterpret_cast<char *>(&circulation), sizeof(circulation));
    inFile.close();
}

// Переопределенный метод для сохранения данных FictionBook в .txt.
void FictionBook::saveToTextFile(const char *filename) const {
    std::ofstream outFile(filename);
    if (!outFile.is_open()) {
        std::cerr << "errorOpeningFileForWriting" << std::endl;
        return;
    }
    outFile << "Title: " << (title ? title : "Unknown") << std::endl;
    outFile << "Author: " << (author ? author : "Unknown") << std::endl;
    outFile << "Pages: " << pages << std::endl;
    outFile << "Circulation: " << circulation << std::endl;
    outFile.close();
}