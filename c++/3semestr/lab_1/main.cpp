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
        // Копируем название книги в динамическую память
        this->title = copyString(title);
    }

    // Конструктор копирования
    Book(const Book &other) : pages(other.pages), circulation(other.circulation) {
        // Копируем название книги из другого объекта
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
        // Если название книги равно nullptr, заменяем его на пустую строку
        const char *thisTitle = this->title ? this->title : "";
        const char *otherTitle = other.title ? other.title : "";

        // Вычисляем длину нового названия (объединение двух строк с " & " между ними)
        // " & " + null terminator
        size_t newTitleLen = strlen(thisTitle) + strlen(otherTitle) + 4;
        // Выделяем память для нового названия
        char *newTitle = new char[newTitleLen];
        // Копируем название первой книги
        strcpy(newTitle, thisTitle);
        strcat(newTitle, " & ");
        // Копируем название второй книги
        strcat(newTitle, otherTitle);

        // Создаём новый объект книги с объединённым названием и суммированными страницами и тиражом
        Book newBook(newTitle, this->pages + other.pages, this->circulation + other.circulation);
        // Освобождаем временно выделенную память для нового названия
        delete[] newTitle;
        // Возвращаем новый объект книги
        return newBook;
    }

    // Функция для изменения данных книги
    void setBook(const char *title, int pages, int circulation) {
        // Освобождаем старое название
        delete[] this->title;
        // Копируем новое название книги
        this->title = copyString(title);
        // Обновляем количество страниц
        this->pages = pages;
        // Обновляем тираж
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
        // Освобождаем память, занятую названием книги
        delete[] title;
    }
};

int main() {
    // Создаём объекты книг с параметрами
    Book book1("The Great Gatsby", 218, 50000);
    Book book2("1984", 328, 75000);

    std::cout << "Book 1:" << std::endl;
    // Информация о первой книге
    book1.display();

    std::cout << "\nBook 2:" << std::endl;
    // Информация о второй книге
    book2.display();

    // Объединяем книги и выводим результат
    Book combinedBook = book1 + book2;
    std::cout << "\nCombined Book:" << std::endl;
    combinedBook.display();

    // Тестируем случай с nullptr в названии
    // Создаём книгу с пустым названием
    Book book3(nullptr, 100, 1000);
    // Объединяем первую и вторую книгу
    combinedBook = book1 + book2;
    std::cout << "\nCombined Book (with nullptr title):" << std::endl;
    // Выводим объединённую книгу с пустым названием
    combinedBook.display();
    // Объединяем первую книгу с книгой с пустым названием
    combinedBook = book1 + book3;
    std::cout << "\nCombined Book (book1 + book3):" << std::endl;
    // Выводим результат объединения
    combinedBook.display();

    return 0;
}
