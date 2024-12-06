//
// Created by vremyavnikuda on 14.11.2024.
//
#include <iostream>
#include <fstream>
#include <cstring>

class Book {
private:
    char *title;
    int pages;
    int circulation;

    // Функция для копирования строки в динамическую память
    char *copyString(const char *str) {
        if (str == nullptr) {
            return nullptr;
        }
        size_t length = strlen(str) + 1;
        char *newStr = new char[length];
        strcpy(newStr, str);
        return newStr;
    }

public:
    // Конструктор по умолчанию
    Book() : title(nullptr), pages(0), circulation(0) {
    }

    // Конструктор с параметрами для инициализации книги
    Book(const char *title, int pages, int circulation) : pages(pages), circulation(circulation) {
        this->title = copyString(title);
    }

    // Конструктор копирования
    Book(const Book &other) : pages(other.pages), circulation(other.circulation) {
        title = copyString(other.title);
    }

    // Оператор присваивания
    Book &operator=(const Book &other) {
        if (this == &other) {
            return *this;
        }
        delete[] title;
        title = copyString(other.title);
        pages = other.pages;
        circulation = other.circulation;
        return *this;
    }

    // Оператор сложения для комбинирования двух книг
    Book operator+(const Book &other) const {
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

    // Дружеская функция для вычитания
    friend Book operator-(const Book &lhs, const Book &rhs) {
        const char *newTitle = "Difference";
        int newPages = lhs.pages - rhs.pages;
        int newCirculation = lhs.circulation - rhs.circulation;

        return Book(newTitle, newPages, newCirculation);
    }

    // Префиксный инкремент
    Book &operator++() {
        ++pages;
        ++circulation;
        return *this;
    }

    // Постфиксный инкремент
    Book operator++(int) {
        Book temp(*this);
        ++pages;
        ++circulation;
        return temp;
    }

    // Приведение типа к int
    operator int() const {
        return pages + circulation;
    }

    // Метод для изменения данных книги
    void setBook(const char *title, int pages, int circulation) {
        delete[] this->title;
        this->title = copyString(title);
        this->pages = pages;
        this->circulation = circulation;
    }

    // Функция для отображения информации о книге
    void display() const {
        std::cout << "Title: " << (title ? title : "Unknown") << std::endl;
        std::cout << "Pages: " << pages << std::endl;
        std::cout << "Circulation: " << circulation << std::endl;
    }

    // Перегрузка оператора вывода в текстовый файл
    friend std::ostream &operator<<(std::ostream &os, const Book &book) {
        os << "Title: " << (book.title ? book.title : "Unknown") << "\n"
                << "Pages: " << book.pages << "\n"
                << "Circulation: " << book.circulation << "\n";
        return os;
    }

    // Перегрузка оператора ввода из текстового файла
    friend std::istream &operator>>(std::istream &is, Book &book) {
        char buffer[256];
        std::cout << "Enter title: ";
        // Игнорируем символ новой строки
        is.ignore();
        is.getline(buffer, 256);
        book.title = book.copyString(buffer);

        std::cout << "Enter number of pages: ";
        is >> book.pages;

        std::cout << "Enter circulation: ";
        is >> book.circulation;

        return is;
    }

    // Сохранение объекта в двоичный файл
    void saveToBinaryFile(const char *filename) const {
        std::ofstream outFile(filename, std::ios::binary);
        if (!outFile.is_open()) {
            std::cerr << "Error opening file for writing!" << std::endl;
            return;
        }

        size_t titleLength = strlen(title) + 1;
        outFile.write(reinterpret_cast<const char *>(&titleLength), sizeof(titleLength));
        outFile.write(title, titleLength);
        outFile.write(reinterpret_cast<const char *>(&pages), sizeof(pages));
        outFile.write(reinterpret_cast<const char *>(&circulation), sizeof(circulation));
        outFile.close();
    }

    // Загрузка объекта из двоичного файла
    void loadFromBinaryFile(const char *filename) {
        std::ifstream inFile(filename, std::ios::binary);
        if (!inFile.is_open()) {
            std::cerr << "Error opening file for reading!" << std::endl;
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

    // Деструктор для освобождения памяти
    ~Book() {
        delete[] title;
    }
};

// main функция
int main() {
    Book book1("The Great Gatsby", 218, 50000);
    Book book2("1984", 328, 75000);

    std::cout << "Book 1:" << std::endl;
    book1.display();

    std::cout << "\nBook 2:" << std::endl;
    book2.display();

    // Операция сложения
    Book combinedBook = book1 + book2;
    std::cout << "\nCombined Book (book1 + book2):" << std::endl;
    combinedBook.display();

    // Сохранение объекта в текстовый файл
    std::ofstream outFile("book1.txt");
    if (outFile.is_open()) {
        outFile << book1;
        outFile.close();
    } else {
        std::cerr << "Error opening file for writing!" << std::endl;
    }

    // Ввод объекта из текстового файла
    Book bookFromFile;
    std::ifstream inFile("book2.txt");
    if (inFile.is_open()) {
        inFile >> bookFromFile;
        inFile.close();
    } else {
        std::cerr << "Error opening file for reading!" << std::endl;
    }

    std::cout << "\nBook from file:" << std::endl;
    bookFromFile.display();

    // Сохранение в двоичный файл
    book1.saveToBinaryFile("book1.bin");

    // Загрузка из двоичного файла
    Book bookFromBinaryFile;
    bookFromBinaryFile.loadFromBinaryFile("book1.bin");

    std::cout << "\nBook from binary file:" << std::endl;
    bookFromBinaryFile.display();

    return 0;
}
