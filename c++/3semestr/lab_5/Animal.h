#ifndef ANIMAL_H
#define ANIMAL_H

// Класс животного
class Animal {
protected:
    // Имя животного
    char *name;

public:
    // Конструктор, который копирует имя животного из входной строки
    Animal(const char *n);

    // Виртуальный деструктор для корректного удаления производных классов
    virtual ~Animal();

    // Виртуальная функция для отображения имени животного
    virtual void display() const;

    // Функция для получения имени животного
    const char* getName() const;
};

#endif