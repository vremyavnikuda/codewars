#include "runTask.h"
#include <iostream>
#include "Book.h"
#include "FictionBook.h"
#include "Textbook.h"

void runTask() {
    // Создаем объекты FictionBook и Textbook
    FictionBook fb("1984", 328, 500000, "George Orwell");
    Textbook tb("The Art of Computer Programming", 5460, 500000, "Computer Science", 1);

    // Отображаем информацию о книгах
    std::cout << "Original -> FictionBook:\n";
    fb.display();
    std::cout << "\nOriginal -> Textbook:\n";
    tb.display();

    std::cout << "\n========================\n";
    // Создаем копии объектов
    FictionBook fbCopy = fb;
    Textbook tbCopy = tb;

    // Отображаем копии
    std::cout << "\nCopied FictionBook:\n";
    fbCopy.display();
    std::cout << "\nCopied Textbook:\n";
    tbCopy.display();
    std::cout << "\n========================\n";

    // Используем указатели на базовый класс для полиморфизма
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
    // Проверка перегрузки оператора сложения
    // Пример сложения одинаковых объектов
    Book combinedBook = fb + fb;
    std::cout << "\nFictionBook + FictionBook:\n";
    combinedBook.display();

    // Сохранение данных в файлы
    fb.saveToBinaryFile("fb.bin");
    fb.saveToTextFile("fb.txt");

    tb.saveToBinaryFile("tb.bin");
    tb.saveToTextFile("tb.txt");

    std::cout << "\n========================\n";
    // Загрузка данных из бинарных файлов
    FictionBook fbLoaded;
    fbLoaded.loadFromBinaryFile("fb.bin");
    std::cout << "\nFictionBook loaded from file:\n";
    fbLoaded.display();

    Textbook tbLoaded;
    tbLoaded.loadFromBinaryFile("tb.bin");
    std::cout << "\nTextbook loaded from file:\n";
    tbLoaded.display();
}
