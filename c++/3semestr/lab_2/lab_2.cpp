//
// Created by vremyavnikuda on 05.11.2024.
//
#include <iostream>
#include <cstring>

class Book {
private:
    // Указатель на строку для хранения названия книги
    char *title;
    // Количество страниц книги
    int pages;
    // Тираж книги
    int circulation;

    // Функция для копирования строки в динамическую память
    char *copyString(const char *str) {
        if (str == nullptr) {
            // Если строка пустая, возвращаем nullptr
            return nullptr;
        }
        // Выделяем память для новой строки
        char *newStr = new char[strlen(str) + 1];
        // Копируем содержимое строки
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
            // Проверка на самоприсваивание
            return *this;
        }
        // Освобождаем память, занятую текущим названием книги
        delete[] title;
        // Копируем новое название
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

        // Создаём временный объект книги
        Book tempBook(newTitle, this->pages + other.pages, this->circulation + other.circulation);
        delete[] newTitle;

        return tempBook;
    }

    // Дружеская функция для вычитания (возвращает книгу с разницей страниц и тиража)
    friend Book operator-(const Book &lhs, const Book &rhs) {
        // Прямое использование строкового литерала без выделения динамической памяти
        const char* newTitle = "Difference";
        int newPages = lhs.pages - rhs.pages;
        int newCirculation = lhs.circulation - rhs.circulation;

        return Book(newTitle, newPages, newCirculation);
    }

    // Префиксный инкремент (увеличивает тираж и страницы)
    Book &operator++() {
        ++pages;
        ++circulation;
        return *this;
    }

    // Постфиксный инкремент (увеличивает тираж и страницы)
    Book operator++(int) {
        // Сохраняем текущий объект
        Book temp(*this);
        ++pages;
        ++circulation;
        // Возвращаем старое состояние объекта
        return temp;
    }

    // Приведение типа к int (сумма страниц и тиража)
    operator int() const {
        return pages + circulation;
    }

    // Функция для изменения данных книги
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

    // Деструктор для освобождения динамически выделенной памяти
    ~Book() {
        delete[] title;
    }
};


//main
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

    // Операция вычитания
    Book diffBook = book1 - book2;
    std::cout << "\nDifference Book (book1 - book2):" << std::endl;
    diffBook.display();

    // Префиксный инкремент
    ++book1;
    std::cout << "\nAfter Prefix Increment (book1):" << std::endl;
    book1.display();

    // Постфиксный инкремент
    book2++;
    std::cout << "\nAfter Postfix Increment (book2):" << std::endl;
    book2.display();

    // Приведение к int (сумма страниц и тиража)
    int book1Data = int(book1);
    std::cout << "\nSum of pages and circulation of book1: " << book1Data << std::endl;

    return 0;
}