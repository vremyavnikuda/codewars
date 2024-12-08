#include "CircularLinkedList.h"
#include <cstring>
#include <iostream>

#include "MemoryException.h"

// Конструктор класса CircularLinkedList
CircularLinkedList::CircularLinkedList() : head(nullptr) {
}

// Деструктор класса CircularLinkedList
CircularLinkedList::~CircularLinkedList() {
    try {
        // Проверяем, если список не пуст
        if (head) {
            Node *current = head;
            do {
                Node *temp = current;
                current = current->next;
                // Освобождаем память для объекта Animal
                delete temp->data;
                delete temp; // Освобождаем память для узла
            } while (current != head);
        }
    } catch (const std::exception &e) {
        std::cerr << "Error: " << e.what() << std::endl;
        // Прокидываем исключение дальше
        throw;
    }
}

// Метод для добавления элемента в конец списка
void CircularLinkedList::addToEnd(Animal *animal) {
    try {
        // Создаем новый с данным животным
        Node *newNode = new Node{animal, nullptr};
        if (!newNode) throw MemoryException();

        if (!head) {
            head = newNode;
            newNode->next = head;
        } else {
            Node *current = head;
            while (current->next != head) {
                current = current->next;
            }
            current->next = newNode;
            newNode->next = head;
        }
    } catch (const std::exception &e) {
        std::cerr << "Error: " << e.what() << std::endl;
        // Прокидываем исключение дальше
        throw;
    }
}

// Метод для вставки элемента по заданному индексу
void CircularLinkedList::insertAt(int index, Animal *animal) {
    try {
        // Проверка на отрицательный индекс
        if (index < 0) throw IndexOutOfRangeException();

        Node *newNode = new Node{animal, nullptr};
        // Проверка на успешное выделение памяти
        if (!newNode) throw MemoryException();

        if (index == 0) {
            if (!head) {
                head = newNode;
                newNode->next = head;
            } else {
                Node *current = head;
                while (current->next != head) {
                    current = current->next;
                }
                current->next = newNode;
                newNode->next = head;
                head = newNode;
            }
            return;
        }

        Node *current = head;
        for (int i = 0; i < index - 1; ++i) {
            if (current->next == head) throw IndexOutOfRangeException();
            current = current->next;
        }

        newNode->next = current->next;
        current->next = newNode;
    } catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
        // Прокидываем исключение дальше
        throw;
    }
}

// Метод для удаления элемента по индексу
void CircularLinkedList::removeAt(int index) {
    try {
        if (index < 0 || !head) throw IndexOutOfRangeException();

        if (index == 0) {
            if (head->next == head) {
                delete head->data;
                delete head;
                head = nullptr;
            } else {
                Node *current = head;
                while (current->next != head) {
                    current = current->next;
                }
                Node *temp = head;
                current->next = head->next;
                head = head->next;
                delete temp->data;
                delete temp;
            }
            return;
        }

        Node *current = head;
        for (int i = 0; i < index - 1; ++i) {
            if (current->next == head) throw IndexOutOfRangeException();
            current = current->next;
        }

        Node *temp = current->next;
        current->next = temp->next;
        delete temp->data;
        delete temp;
    } catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
        // Прокидываем исключение дальше
        throw;
    }
}

// Метод для поиска элемента по имени
Animal *CircularLinkedList::findByName(const char *name) {
    try {
        if (!head) return nullptr;

        Node *current = head;
        do {
            if (strcmp(current->data->getName(), name) == 0) {
                return current->data;
            }
            current = current->next;
        } while (current != head);

        return nullptr;
    } catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
        // Прокидываем исключение дальше
        throw;
    }
}

// Метод для вывода всех элементов списка
void CircularLinkedList::displayAll() const {
    try {
        if (!head) {
            std::cout << "The list is empty." << std::endl;
            return;
        }

        Node *current = head;
        do {
            current->data->display();
            current = current->next;
        } while (current != head);
    } catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
        // Прокидываем исключение дальше
        throw;
    }
}
