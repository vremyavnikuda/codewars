#include "Book.h"
#include <iostream>
#include <fstream>

int main() {
    // Создание двух объектов книг с параметрами: название, количество страниц, тираж
    Book book1("The Great Gatsby", 218, 50000);
    Book book2("1984", 328, 75000);

    // Вывод информации о первой книге
    std::cout << "Book 1:" << std::endl;
    book1.display();

    // Вывод информации о второй книге
    std::cout << "\nBook 2:" << std::endl;
    book2.display();

    // Сохранение второй книги в текстовый файл в корень проекта
    // Путь с "./" указывает на текущую директорию (корень проекта)
    std::ofstream outFile2("./lab_3/book2.txt");
    if (outFile2.is_open()) {
        outFile2 << book2;
        outFile2.close();
    } else {
        std::cerr << "Error opening file for writing book2.txt!" << std::endl;
    }

    // Операция сложения двух книг: объединение названий и суммирование страниц и тиражей
    Book combinedBook = book1 + book2;
    std::cout << "\nCombined Book (book1 + book2):" << std::endl;
    combinedBook.display(); // Вывод комбинированной книги

    // Сохранение первой книги в текстовый файл в корень проекта
    // Путь с "./" указывает на текущую директорию (корень проекта)
    std::ofstream outFile("./lab_3/book1.txt");
    if (outFile.is_open()) {
        outFile << book1;
        outFile.close();
    } else {
        std::cerr << "Error opening file for writing book1.txt!" << std::endl;
    }

    // Чтение второй книги из текстового файла, находящегося в корне проекта
    Book bookFromFile;
    // Путь с "./" указывает на текущую директорию (корень проекта)
    std::ifstream inFile("./lab_3/book2.txt");
    if (inFile.is_open()) {
        inFile >> bookFromFile;
        inFile.close();
    } else {
        std::cerr << "Error opening file for reading book2.txt!" << std::endl;
    }

    // Вывод информации о книге, прочитанной из файла
    std::cout << "\nBook from file:" << std::endl;
    bookFromFile.display();

    // Сохранение первой книги в бинарный файл в корне проекта
    // Путь с "./" указывает на текущую директорию (корень проекта)
    book1.saveToBinaryFile("./lab_3/book1.bin");

    // Загрузка первой книги из бинарного файла, находящегося в корне проекта
    Book bookFromBinaryFile;
    // Путь с "./" указывает на текущую директорию (корень проекта)
    bookFromBinaryFile.loadFromBinaryFile("./book1.bin");

    // Вывод информации о книге, загруженной из бинарного файла
    std::cout << "\nBook from binary file:" << std::endl;
    bookFromBinaryFile.display();

    return 0;
}
