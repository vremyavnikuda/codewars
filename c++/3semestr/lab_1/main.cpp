#include "Book.h"
#include <iostream>

int main() {
    // Создаем объекты
    Book book1("The Great Gatsby", 218, 50000);
    Book book2("1984", 328, 75000);

    //Выводим информацию о book1
    std::cout << "Book 1:" << std::endl;
    book1.display();

    // Выводим информацию о book2
    std::cout << "\nBook 2:" << std::endl;
    book2.display();

    // Создаем новую книгу методом сложения book1 + book2
    Book combinedBook = book1 + book2;
    std::cout << "\nCombined Book:" << std::endl;
    // Выводим информацию о combinedBook
    combinedBook.display();

    // Создание книги с nullptr в качестве названия (неправильный параметр для названия)
    Book book3(nullptr, 100, 1000);
    // Сложение book1 с книгой book3, где у book3 название равно nullptr
    combinedBook = book1 + book3;
    std::cout << "\nCombined Book (book1 + book3):" << std::endl;
    combinedBook.display();

    return 0;
}
