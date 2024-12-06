// Created by vremyavnikuda on 20.11.2024.

#include <iostream>
#include <fstream>
#include <cstring>

// Базовый класс Book
class Book {
protected:
    // Название книги
    char *title;
    // Количество страниц
    int pages;
    // Тираж книги
    int circulation;

    // Функция для копирования строки в динамическую память
    char *copyString(const char *str) {
        // Если строка пустая, -> nullptr
        if (str == nullptr) return nullptr;
        size_t len = strlen(str) + 1;
        // Выделяем память для новой строки
        char *newStr = new char[len];
        // Копируем строку
        strcpy(newStr, str);
        return newStr;
    }

public:
    // Конструктор по default
    Book() : title(nullptr), pages(0), circulation(0) {
    }

    // Конструктор с параметрами для инициализации книги
    Book(const char *t, int p, int c) : pages(p), circulation(c) {
        // Копируем название книги
        title = copyString(t);
    }

    // Конструктор копирования
    Book(const Book &other) : pages(other.pages), circulation(other.circulation) {
        // Копируем данные из другого объекта
        title = copyString(other.title);
    }

    // Деструктор для освобождения памяти
    virtual ~Book() {
        // Освобождаем память, выделенную для названия книги
        delete[] title;
    }

    // Оператор присваивания (=)
    Book &operator=(const Book &other) {
        if (this != &other) {
            // Проверка
            // Освобождаем память, если она была выделена
            delete[] title;
            // Копируем новое название
            title = copyString(other.title);
            pages = other.pages;
            circulation = other.circulation;
        }
        return *this;
    }

    // Оператор сложения (+) для комбинирования двух книг
    Book operator+(const Book &other) const {
        const char *thisTitle = this->title ? this->title : "";
        const char *otherTitle = other.title ? other.title : "";

        size_t newTitleLen = strlen(thisTitle) + strlen(otherTitle) + 4;
        // Выделяем память для newTitle
        char *newTitle = new char[newTitleLen];
        strcpy(newTitle, thisTitle);
        // Добавляем разделитель  "&"
        strcat(newTitle, " & ");
        strcat(newTitle, otherTitle);

        Book tempBook(newTitle, this->pages + other.pages, this->circulation + other.circulation);
        // Создаем новую книгу
        // Подчищаем за собой
        delete[] newTitle;
        return tempBook;
    }

    // Оператор вычитания (-) для книг (разница по страницам и тиражу)
    friend Book operator-(const Book &lhs, const Book &rhs) {
        // Дефолтное название для книги
        const char *newTitle = "Difference";
        int newPages = lhs.pages - rhs.pages;
        int newCirculation = lhs.circulation - rhs.circulation;
        return Book(newTitle, newPages, newCirculation);
    }

    // Префиксный инкремент (увеличение страниц и тиража)
    Book &operator++() {
        ++pages;
        ++circulation;
        return *this;
    }

    // Постфиксный инкремент (возвращаем текущий объект и увеличиваем страницы и тираж)
    Book operator++(int) {
        // save temp состояние
        Book temp(*this);
        ++pages;
        ++circulation;
        return temp;
    }

    // Приведение объекта к типу int (возвращаем сумму страниц и тиража)
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

    // Виртуальная функция для отображения информации о книге
    virtual void display() const {
        std::cout << "Title: " << (title ? title : "Unknown") << std::endl;
        std::cout << "Pages: " << pages << std::endl;
        std::cout << "Circulation: " << circulation << std::endl;
    }

    // Перегрузка оператора вывода в .txt файл
    friend std::ostream &operator<<(std::ostream &os, const Book &book) {
        os << "Title: " << (book.title ? book.title : "Unknown") << "\n"
                << "Pages: " << book.pages << "\n"
                << "Circulation: " << book.circulation << "\n";
        return os;
    }

    // Перегрузка оператора ввода из .txt файла
    friend std::istream &operator>>(std::istream &is, Book &book) {
        char buffer[256];
        std::cout << "Enter title: ";
        // Игнорируем символ новой строки
        is.ignore();
        // Считываем название книги
        is.getline(buffer, 256);
        book.title = book.copyString(buffer);

        std::cout << "Enter number of pages: ";
        is >> book.pages;

        std::cout << "Enter circulation: ";
        is >> book.circulation;
        return is;
    }

    // virtual функция для сохранения книги в .bin файл
    virtual void saveToBinaryFile(const char *filename) const {
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

    // virtual функция для загрузки книги из .bin файла
    virtual void loadFromBinaryFile(const char *filename) {
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

    // virtual функция для сохранения книги в .txt файл
    virtual void saveToTextFile(const char *filename) const {
        std::ofstream outFile(filename);
        if (!outFile.is_open()) {
            std::cerr << "Error opening file for writing!" << std::endl;
            return;
        }
        outFile << "Title: " << (title ? title : "Unknown") << std::endl;
        outFile << "Pages: " << pages << std::endl;
        outFile << "Circulation: " << circulation << std::endl;
        outFile.close();
    }
};

// Производный класс для художественных книг
class FictionBook : public Book {
private:
    // Автор книги
    char *author;

public:
    FictionBook() : Book(), author(nullptr) {
    }

    FictionBook(const char *t, int p, int c, const char *a)
        : Book(t, p, c), author(copyString(a)) {
    }

    FictionBook(const FictionBook &other)
        : Book(other), author(copyString(other.author)) {
    }

    ~FictionBook() {
        // Подчищаем за собой
        delete[] author;
    }

    FictionBook &operator=(const FictionBook &other) {
        if (this != &other) {
            Book::operator=(other);
            // Подчищаем за собой
            delete[] author;
            author = copyString(other.author);
        }
        return *this;
    }

    // Переопределенный метод display() для отображения информации о FictionBook
    void display() const override {
        Book::display();
        std::cout << "Author: " << (author ? author : "Unknown") << std::endl;
    }

    // Переопределение функции сохранения в .bin файл
    void saveToBinaryFile(const char *filename) const override {
        std::ofstream outFile(filename, std::ios::binary);
        if (!outFile.is_open()) {
            std::cerr << "Error opening file for writing!" << std::endl;
            return;
        }
        size_t titleLength = strlen(title) + 1;
        size_t authorLength = strlen(author) + 1;
        outFile.write(reinterpret_cast<const char *>(&titleLength), sizeof(titleLength));
        outFile.write(title, titleLength);
        outFile.write(reinterpret_cast<const char *>(&pages), sizeof(pages));
        outFile.write(reinterpret_cast<const char *>(&circulation), sizeof(circulation));
        outFile.write(reinterpret_cast<const char *>(&authorLength), sizeof(authorLength));
        outFile.write(author, authorLength);
        outFile.close();
    }

    // Переопределение функции загрузки из .bin файла
    void loadFromBinaryFile(const char *filename) override {
        std::ifstream inFile(filename, std::ios::binary);
        if (!inFile.is_open()) {
            std::cerr << "Error opening file for reading!" << std::endl;
            return;
        }
        size_t titleLength, authorLength;
        inFile.read(reinterpret_cast<char *>(&titleLength), sizeof(titleLength));
        delete[] title;
        title = new char[titleLength];
        inFile.read(title, titleLength);
        inFile.read(reinterpret_cast<char *>(&pages), sizeof(pages));
        inFile.read(reinterpret_cast<char *>(&circulation), sizeof(circulation));
        inFile.read(reinterpret_cast<char *>(&authorLength), sizeof(authorLength));
        delete[] author;
        author = new char[authorLength];
        inFile.read(author, authorLength);
        inFile.close();
    }

    // Переопределение функции сохранения в .txt файл
    void saveToTextFile(const char *filename) const override {
        std::ofstream outFile(filename);
        if (!outFile.is_open()) {
            std::cerr << "Error opening file for writing!" << std::endl;
            return;
        }
        outFile << "Title: " << (title ? title : "Unknown") << std::endl;
        outFile << "Pages: " << pages << std::endl;
        outFile << "Circulation: " << circulation << std::endl;
        outFile << "Author: " << (author ? author : "Unknown") << std::endl;
        outFile.close();
    }
};

// Производный класс: учебник(и)
class Textbook : public Book {
private:
    // Предмет
    char *subject;
    // lvl учебника
    int level;

public:
    Textbook() : Book(), subject(nullptr), level(0) {
    }

    Textbook(const char *t, int p, int c, const char *s, int l)
        : Book(t, p, c), subject(copyString(s)), level(l) {
    }

    Textbook(const Textbook &other)
        : Book(other), subject(copyString(other.subject)), level(other.level) {
    }

    ~Textbook() {
        // Подчищаем за собой
        delete[] subject;
    }

    Textbook &operator=(const Textbook &other) {
        if (this != &other) {
            Book::operator=(other);
            delete[] subject;
            subject = copyString(other.subject);
            level = other.level;
        }
        return *this;
    }

    // Переопределение display() для отображения информации о учебнике
    void display() const override {
        Book::display();
        std::cout << "Subject: " << (subject ? subject : "Unknown") << std::endl;
        std::cout << "Level: " << level << std::endl;
    }

    // Переопределение функции сохранения в .bin файл
    void saveToBinaryFile(const char *filename) const override {
        std::ofstream outFile(filename, std::ios::binary);
        if (!outFile.is_open()) {
            std::cerr << "Error opening file for writing!" << std::endl;
            return;
        }
        size_t titleLength = strlen(title) + 1;
        size_t subjectLength = strlen(subject) + 1;
        outFile.write(reinterpret_cast<const char *>(&titleLength), sizeof(titleLength));
        outFile.write(title, titleLength);
        outFile.write(reinterpret_cast<const char *>(&pages), sizeof(pages));
        outFile.write(reinterpret_cast<const char *>(&circulation), sizeof(circulation));
        outFile.write(reinterpret_cast<const char *>(&subjectLength), sizeof(subjectLength));
        outFile.write(subject, subjectLength);
        outFile.write(reinterpret_cast<const char *>(&level), sizeof(level));
        outFile.close();
    }

    // Переопределение функции загрузки из .bin файла
    void loadFromBinaryFile(const char *filename) override {
        std::ifstream inFile(filename, std::ios::binary);
        if (!inFile.is_open()) {
            std::cerr << "Error opening file for reading!" << std::endl;
            return;
        }
        size_t titleLength, subjectLength;
        inFile.read(reinterpret_cast<char *>(&titleLength), sizeof(titleLength));
        delete[] title;
        title = new char[titleLength];
        inFile.read(title, titleLength);
        inFile.read(reinterpret_cast<char *>(&pages), sizeof(pages));
        inFile.read(reinterpret_cast<char *>(&circulation), sizeof(circulation));
        inFile.read(reinterpret_cast<char *>(&subjectLength), sizeof(subjectLength));
        delete[] subject;
        subject = new char[subjectLength];
        inFile.read(subject, subjectLength);
        inFile.read(reinterpret_cast<char *>(&level), sizeof(level));
        inFile.close();
    }

    // Переопределение функции сохранения в .txt файл
    void saveToTextFile(const char *filename) const override {
        std::ofstream outFile(filename);
        if (!outFile.is_open()) {
            std::cerr << "Error opening file for writing!" << std::endl;
            return;
        }
        outFile << "Title: " << (title ? title : "Unknown") << std::endl;
        outFile << "Pages: " << pages << std::endl;
        outFile << "Circulation: " << circulation << std::endl;
        outFile << "Subject: " << (subject ? subject : "Unknown") << std::endl;
        outFile << "Level: " << level << std::endl;
        outFile.close();
    }
};

// Функция startTask
static void startTask() {
    // Создание объектов
    // FictionBook
    FictionBook fb("1984", 328, 500000, "George Orwell");
    // Textbook
    Textbook tb("The Art of Computer Programming", 5460, 500000, "Computer Science", 1);

    // Оригинальные объекты
    std::cout << "Original -> FictionBook:\n";
    fb.display();
    std::cout << "\nOriginal -> Textbook:\n";
    tb.display();

    std::cout << "\n========================\n";
    // Копии объектов
    FictionBook fbCopy = fb;
    Textbook tbCopy = tb;

    std::cout << "\nCopied FictionBook:\n";
    fbCopy.display();
    std::cout << "\nCopied Textbook:\n";
    tbCopy.display();
    std::cout << "\n========================\n";
    // Использование указателей базового класса для полиморфизма
    Book *bookPtr1 = new FictionBook(fb);
    Book *bookPtr2 = new Textbook(tb);

    std::cout << "\nDisplaying FictionBook via base pointer:\n";
    bookPtr1->display();
    std::cout << "\nDisplaying Textbook via base pointer:\n";
    bookPtr2->display();

    // Освобождаем память
    delete bookPtr1;
    delete bookPtr2;
    std::cout << "\n========================\n";
    // Перегрузка операторов
    // Проверка сложения двух книг
    Book combinedBook = fb + fb; // Пример сложения одинаковых объектов
    std::cout << "\nFictionBook + FictionBook:\n";
    combinedBook.display();

    // Сохранение в файлы
    fb.saveToBinaryFile("fb.bin");
    fb.saveToTextFile("fb.txt");

    tb.saveToBinaryFile("tb.bin");
    tb.saveToTextFile("tb.txt");
    std::cout << "\n========================\n";
    // Загрузка данных из двоичных файлов
    FictionBook fbLoaded;
    fbLoaded.loadFromBinaryFile("fb.bin");
    std::cout << "\nFictionBook loaded from file:\n";
    fbLoaded.display();

    Textbook tbLoaded;
    tbLoaded.loadFromBinaryFile("tb.bin");
    std::cout << "\nTextbook loaded from file:\n";
    tbLoaded.display();
}

// main функция
int main() {
    startTask();
    return 0;
}
