#include <iostream>
#include <cstring>

class Book {
private:
    // выделение памяти для названия
    char *title;
    // Количество страниц
    int pages;
    // Тираж
    int circulation;
    // Функция для копирования строки
    char *copyString(const char *str) {
        if (str == nullptr) {
            return nullptr;
        }
        char *newStr = new char[strlen(str) + 1];
        strcpy(newStr, str);
        return newStr;
    }

public:
    // Конструктор по умолчанию
    Book() : title(nullptr), pages(0), circulation(0) {
    }

    // Конструктор с параметрами
    Book(const char *title, int pages, int circulation)
        : pages(pages), circulation(circulation) {
        this->title = copyString(title);
    }

    // Конструктор копирования
    Book(const Book &other) {
        title = copyString(other.title);
        pages = other.pages;
        circulation = other.circulation;
    }

    // Оператор присваивания
    Book &operator=(const Book &other) {
        if (this == &other) {
            return *this;
        }

        // Освобождение старой памяти
        delete[] title;

        // Копирование данных
        title = copyString(other.title);
        pages = other.pages;
        circulation = other.circulation;

        return *this;
    }

    // Оператор сложения
    Book operator+(const Book &other) const {
        char *newTitle = new char[strlen(this->title) + strlen(other.title) + 4];
        strcpy(newTitle, this->title);
        strcat(newTitle, " & ");
        strcat(newTitle, other.title);

        Book newBook(newTitle, this->pages + other.pages, this->circulation + other.circulation);
        delete[] newTitle;
        return newBook;
    }

    // Метод для изменения данных книги
    void setBook(const char *title, int pages, int circulation);

    // Метод для вывода информации о книге
    void display() const {
        std::cout << "Title: " << (title ? title : "Unknown") << std::endl;
        std::cout << "Pages: " << pages << std::endl;
        std::cout << "Circulation: " << circulation << std::endl;
    }

    // Деструктор
    ~Book() {
        delete[] title;
    }
};

void Book::setBook(const char *title, int pages, int circulation) {
    delete[] this->title;

    this->title = copyString(title);
    this->pages = pages;
    this->circulation = circulation;
}

int main() {
    // Создание объектов класса Book
    Book book1("The Great Gatsby", 218, 50000);
    Book book2("1984", 328, 75000);

    // Вывод информации о книгах
    std::cout << "Book 1:" << std::endl;
    book1.display();

    std::cout << "\nBook 2:" << std::endl;
    book2.display();

    // Сложение двух объектов(книг)
    Book combinedBook = book1 + book2;
    std::cout << "\nCombined Book:" << std::endl;
    combinedBook.display();

    return 0;
}
