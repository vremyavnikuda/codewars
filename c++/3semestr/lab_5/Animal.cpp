#include "Animal.h"
#include <cstring>
#include <iostream>

// Имплементация класса Animal

// Конструктор класса Animal
Animal::Animal(const char *n) {
    name = new char[strlen(n) + 1];
    strcpy(name, n);
}

// Деструктор класса Animal
Animal::~Animal() {
    delete[] name;
}

// Функция отображения информации об животном
void Animal::display() const {
    std::cout << "Animal Name: " << name << std::endl;
}

// Функция для получения имени животного
const char* Animal::getName() const {
    return name;
}