#ifndef CAT_H
#define CAT_H

#include "Animal.h"

// Класс Cat, наследующийся от класса Animal
class Cat : public Animal {
public:
    Cat(const char *n);

    // Переопределяем функцию display() из базового класса
    void display() const override;
};

#endif
