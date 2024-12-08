#include "Animal.h"
#include <cstring>
#include <iostream>
#include <stdexcept>

#include "MemoryException.h"


// Конструктор класса Animal
Animal::Animal(const char *n) {
    try {
        name = new char[strlen(n) + 1];
        if (!name) throw MemoryException();
        strcpy(name, n);
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        // Прокидываем исключение дальше
        throw;
    }
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
