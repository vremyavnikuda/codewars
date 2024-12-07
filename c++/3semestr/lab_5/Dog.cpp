#include "Dog.h"
#include <iostream>

// Конструктор класса Dog, инициализирующий имя собаки
Dog::Dog(const char *n) : Animal(n) {}

// Реализация функции display() для вывода имени собаки
void Dog::display() const {
    std::cout << "Dog Name: " << name << std::endl;
}