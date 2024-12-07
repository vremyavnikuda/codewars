#include "Textbook.h"
#include <cstring>
#include <fstream>

// Конструктор по умолчанию для Textbook, инициализирует base class Book и level
Textbook::Textbook() : Book(), level(0) {
}

// Конструктор инициализации с параметрами: название, количество страниц, тираж и уровень
Textbook::Textbook(const char *t, int p, int c, int l) : Book(t, p, c), level(l) {
}

// Конструктор копирования для Textbook, копирует данные из другого объекта Textbook
Textbook::Textbook(const Textbook &other) : Book(other), level(other.level) {
}

// Дополнительный конструктор, инициализирующий base class Book и level
Textbook::Textbook(const char *str, int i, int i1, const char *text, int i2) : Book(str, i, i1), level(i2) {
}

// Деструктор для Textbook, в данном случае пустой, так как очистка памяти происходит в base class
Textbook::~Textbook() {
}

// Оператор присваивания для Textbook, копирует данные из другого объекта Textbook
Textbook &Textbook::operator=(const Textbook &other) {
    if (this != &other) {
        Book::operator=(other);
        level = other.level;
    }
    return *this;
}

// Переопределенный метод display, выводит информацию о книге и уровень
void Textbook::display() const {
    Book::display();
    std::cout << "Level: " << level << std::endl;
}

// Метод для сохранения данных Textbook в .bin
void Textbook::saveToBinaryFile(const char *filename) const {
    std::ofstream outFile(filename, std::ios::binary);
    if (!outFile.is_open()) {
        std::cerr << "Ошибка открытия файла для записи!" << std::endl;
        return;
    }
    size_t titleLength = strlen(title) + 1;
    outFile.write(reinterpret_cast<const char *>(&titleLength), sizeof(titleLength));
    outFile.write(title, titleLength);
    outFile.write(reinterpret_cast<const char *>(&level), sizeof(level));
    outFile.write(reinterpret_cast<const char *>(&pages), sizeof(pages));
    outFile.write(reinterpret_cast<const char *>(&circulation), sizeof(circulation));
    outFile.close();
}

// Метод для загрузки данных Textbook из .bin файла
void Textbook::loadFromBinaryFile(const char *filename) {
    std::ifstream inFile(filename, std::ios::binary);
    if (!inFile.is_open()) {
        std::cerr << "errorOpeningFileForReading" << std::endl;
        return;
    }
    size_t titleLength;
    inFile.read(reinterpret_cast<char *>(&titleLength), sizeof(titleLength)); // Читаем длину названия
    delete[] title;
    title = new char[titleLength];
    inFile.read(title, titleLength);
    inFile.read(reinterpret_cast<char *>(&level), sizeof(level));
    inFile.read(reinterpret_cast<char *>(&pages), sizeof(pages));
    inFile.read(reinterpret_cast<char *>(&circulation), sizeof(circulation));
    inFile.close();
}

// Метод для сохранения данных Textbook в .txt файл
void Textbook::saveToTextFile(const char *filename) const {
    std::ofstream outFile(filename);
    if (!outFile.is_open()) {
        std::cerr << "errorOpeningFileForWriting" << std::endl;
        return;
    }
    outFile << "Title: " << (title ? title : "Unknown") << std::endl;
    outFile << "Level: " << level << std::endl;
    outFile << "Pages: " << pages << std::endl;
    outFile << "Circulation: " << circulation << std::endl;
    outFile.close();
}
