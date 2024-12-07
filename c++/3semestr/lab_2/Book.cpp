#include "Book.h"
#include <iostream>

// Конструктор по умолчанию:
// Инициализирую title как nullptr, а pages и circulation как 0.
Book::Book() : title(nullptr), pages(0), circulation(0) {
}

// Параметризованный конструктор:
// Инициализирую title (копирую строку), pages и circulation.
Book::Book(const char *title, int pages, int circulation) : pages(pages), circulation(circulation) {
    this->title = copyString(title); // Копирую название книги
}

// Конструктор копирования:
// Создаю новый объект, копируя данные из другого объекта Book.
Book::Book(const Book &other) : pages(other.pages), circulation(other.circulation) {
    title = copyString(other.title); // Копирую название из другого объекта
}

// Оператор присваивания:
// Сначала проверяю, не является ли объект самоприсваиванием,
// затем освобождаю старую память и копирую данные из другого объекта.
Book &Book::operator=(const Book &other) {
    if (this == &other) {
        // Защищаюсь от самоприсваивания
        return *this;
    }
    // Освобождаю старую память
    delete[] title;
    // Копирую новое название
    title = copyString(other.title);
    this->pages = other.pages;
    this->circulation = other.circulation;
    // Возвращаю текущий объект для цепочки присваиваний
    return *this;
}

// Оператор сложения:
// Объединяю названия двух книг (с разделителем " & "), а также суммирую страницы и тираж.
Book Book::operator+(const Book &other) const {
    // Если название одной из книг равно nullptr, использую пустую строку
    const char *thisTitle = this->title ? this->title : "";
    const char *otherTitle = other.title ? other.title : "";

    // Узнаю длину нового названия
    // 4 символа для " & " и нулевого терминирования
    size_t newTitleLen = strlen(thisTitle) + strlen(otherTitle) + 4;
    // Выделяю память для нового названия
    char *newTitle = new char[newTitleLen];
    // Копирую название первой книги
    strcpy(newTitle, thisTitle);
    // Добавляю разделитель " & "
    strcat(newTitle, " & ");
    // Добавляю название второй книги
    strcat(newTitle, otherTitle);

    // Создаю новый объект Book с объединенными данными
    Book tempBook(newTitle, this->pages + other.pages, this->circulation + other.circulation);
    // Освобождаю память для временной строки
    delete[] newTitle;
    // Возвращаю новый объект Book
    return tempBook;
}

// Оператор вычитания:
// Создаю новую книгу с названием "Difference" и вычисляю разницу в страницах и тиражах.
Book operator-(const Book &lhs, const Book &rhs) {
    // Название книги для результата
    const char *newTitle = "Difference";
    // Разница в страницах
    int newPages = lhs.pages - rhs.pages;
    // Разница в тираже
    int newCirculation = lhs.circulation - rhs.circulation;

    // Возвращаю новую книгу с результатом
    return Book(newTitle, newPages, newCirculation);
}

// Префиксная форма оператора инкремента:
// Увеличиваю количество страниц и тиража на 1 и возвращаю текущий объект.
Book &Book::operator++() {
    // Увеличиваю страницы
    ++pages;
    // Увеличиваю тираж
    ++circulation;
    // Возвращаю текущий объект для цепочки вызовов
    return *this;
}

// Постфиксная форма оператора инкремента:
// Создаю копию текущего объекта, увеличиваю страницы и тираж,
// и возвращаю копию (до изменения).
Book Book::operator++(int) {
    Book temp(*this); // Сохраняю копию текущего объекта
    ++pages; // Увеличиваю страницы
    ++circulation; // Увеличиваю тираж
    return temp; // Возвращаю копию до изменения
}

// Оператор приведения к типу int:
// Возвращаю сумму страниц и тиража.
Book::operator int() const {
    return pages + circulation; // Суммирую страницы и тираж
}

// Метод для установки данных о книге:
// Обновляю название, страницы и тираж.
void Book::setBook(const char *title, int pages, int circulation) {
    // Освобождаю старую память для названия
    delete[] this->title;
    // Копирую новое название
    this->title = copyString(title);
    // Устанавливаю новые страницы
    this->pages = pages;
    // Устанавливаю новый тираж
    this->circulation = circulation;
}

// Метод для отображения данных о книге:
// Вывожу название, страницы и тираж на экран.
void Book::display() const {
    std::cout << "Title: " << (title ? title : "Unknown") << std::endl;
    // Вывожу название книги (если оно есть, иначе "Unknown")
    // Вывожу количество страниц
    std::cout << "Pages: " << pages << std::endl;
    // Вывожу тираж
    std::cout << "Circulation: " << circulation << std::endl;
}

// Деструктор:
// Освобождаю память, выделенную для строки title.
Book::~Book() {
    // Освобождаю динамически выделенную память
    delete[] title;
}

// Функция для копирования строки в динамическую память.
char *Book::copyString(const char *str) {
    if (str == nullptr) {
        // Если строка равна nullptr, возвращаю nullptr
        return nullptr;
    }
    // Выделяю память для новой строки
    char *newStr = new char[strlen(str) + 1];
    // Копирую строку
    strcpy(newStr, str);
    // Возвращаю указатель на новую строку
    return newStr;
}
