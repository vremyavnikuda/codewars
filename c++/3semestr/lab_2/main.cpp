#include "Book.h"
#include <iostream>

int main() {
    Book book1("The Great Gatsby", 218, 50000);
    Book book2("1984", 328, 75000);

    std::cout << "Book 1:" << std::endl;
    book1.display();

    std::cout << "\nBook 2:" << std::endl;
    book2.display();

    // Operation +
    Book combinedBook = book1 + book2;
    std::cout << "\nCombined Book (book1 + book2):" << std::endl;
    combinedBook.display();

    // Operation -
    Book diffBook = book1 - book2;
    std::cout << "\nDifference Book (book1 - book2):" << std::endl;
    diffBook.display();

    // Prefix increment
    ++book1;
    std::cout << "\nAfter Prefix Increment (book1):" << std::endl;
    book1.display();

    // Postfix increment
    book2++;
    std::cout << "\nAfter Postfix Increment (book2):" << std::endl;
    book2.display();

    // Conversion to int
    int book1Data = int(book1);
    std::cout << "\nSum of pages and circulation of book1: " << book1Data << std::endl;

    return 0;
}