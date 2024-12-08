#ifndef DOG_H
#define DOG_H

#include "Animal.h"

// Класс Dog, который наследуется от класса Animal
class Dog : public Animal {
public:
    // Конструктор класса Dog, принимающий имя собаки
    Dog(const char *n);

    // Переопределение функции display() для вывода имени собаки
    void display() const override;
};

#endif