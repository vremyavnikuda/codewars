#ifndef CIRCULARLINKEDLIST_H
#define CIRCULARLINKEDLIST_H

#include "Animal.h"

struct Node {
    // Структура для представления узла списка
    // Указатель на данные (объект класса Animal)
    Animal *data;
    // Указатель на следующий узел
    Node *next;
};

class CircularLinkedList {
    // Класс для представления циклического односвязного списка
private:
    // Указатель на голову списка
    Node *head;

public:
    // Конструктор
    CircularLinkedList();

    // Деструктор
    ~CircularLinkedList();

    // Добавить элемент в конец списка
    void addToEnd(Animal *animal);

    // Вставить элемент по указанному индексу
    void insertAt(int index, Animal *animal);

    // Удалить элемент по указанному индексу
    void removeAt(int index);

    // Найти элемент по имени
    Animal *findByName(const char *name);

    // Вывести все элементы списка
    void displayAll() const;
};

#endif
