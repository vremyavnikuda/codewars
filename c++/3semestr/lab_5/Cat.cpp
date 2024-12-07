#include "Cat.h"
#include <iostream>

// Конструктор, инициализирующий базовый класс Animal именем кота
Cat::Cat(const char *n) : Animal(n) {
}

// Переопределение функции display() для вывода имени кота
void Cat::display() const {
    std::cout << "Cat Name: " << name << std::endl;
}
