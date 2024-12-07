#include "CircularLinkedList.h"
#include <cstring>
#include <iostream>

// Конструктор класса CircularLinkedList
CircularLinkedList::CircularLinkedList() : head(nullptr) {}

// Деструктор класса CircularLinkedList
CircularLinkedList::~CircularLinkedList() {
    // Проверяем, если список не пуст
    if (head) {
        Node* current = head;
        do {
            Node* temp = current;
            current = current->next;
            // Освобождаем память для объекта Animal
            delete temp->data;
            // Освобождаем память
            delete temp;
        } while (current != head);
    }
}

// Метод для добавления элемента в конец списка
void CircularLinkedList::addToEnd(Animal* animal) {
    // Создаем новый с данным животным
    Node* newNode = new Node{animal, nullptr};

    if (!head) {
        // Если список пуст, то новый становится head
        head = newNode;
        newNode->next = head;
    } else {
        // Если список не пуст, находим последний и добавляем новый после него
        Node* current = head;
        while (current->next != head) {
            current = current->next;
        }
        current->next = newNode;
        // Новый указывает на head
        newNode->next = head;
    }
}

// Метод для вставки элемента по заданному индексу
void CircularLinkedList::insertAt(int index, Animal* animal) {
    // Проверка на отрицательный индекс
    if (index < 0) return;

    // Создаем новый узел с данным животным
    Node* newNode = new Node{animal, nullptr};

    if (index == 0) {
        // Если индекс равен 0, добавляем новый узел в начало
        if (!head) {
            // Если список пуст, новый узел становится head
            head = newNode;
            newNode->next = head;
        } else {
            // Если список не пуст, находим последний и изменяем указатель
            Node* current = head;
            while (current->next != head) {
                current = current->next;
            }
            current->next = newNode;
            newNode->next = head;
            // Новый узел становится head
            head = newNode;
        }
        return;
    }

    // Если индекс не равен 0, находим узел, перед которым нужно вставить новый
    Node* current = head;
    for (int i = 0; i < index - 1; ++i) {
        // Если дошли до конца списка
        if (current->next == head) break;
        current = current->next;
    }

    // Вставляем новый узел в нужное место
    newNode->next = current->next;
    current->next = newNode;
}

// Метод для удаления элемента по индексу
void CircularLinkedList::removeAt(int index) {
    // Если индекс отрицательный или список пуст
    if (index < 0 || !head) return;

    if (index == 0) {
        // Если удаляется первый элемент
        if (head->next == head) {
            // Если список содержит только один элемент
            // Освобождаем память для объекта Animal
            delete head->data;
            // Освобождаем память
            delete head;
            // Список становится пустым
            head = nullptr;
        } else {
            // Если список содержит больше одного элемента
            Node* current = head;
            while (current->next != head) {
                current = current->next;
            }
            Node* temp = head;
            // Последний указывает на второй элемент
            current->next = head->next;
            // Второй элемент становится head
            head = head->next;
            // Освобождаем память для объекта Animal
            delete temp->data;
            // Освобождаем память
            delete temp;
        }
        return;
    }

    // Если удаляется не первый элемент, находим узел перед удаляемым
    Node* current = head;
    for (int i = 0; i < index - 1; ++i) {
        // Если дошли до конца списка
        if (current->next == head) return;
        current = current->next;
    }

    // Удаляем нужный узел
    Node* temp = current->next;
    current->next = temp->next;
    // Освобождаем память для объекта Animal
    delete temp->data;
    // Освобождаем память
    delete temp;
}

// Метод для поиска элемента по имени
Animal* CircularLinkedList::findByName(const char* name) {
    // Если список пуст
    if (!head) return nullptr;

    Node* current = head;
    do {
        if (strcmp(current->data->getName(), name) == 0) {
            // Если имя совпадает, возвращаем найденный элемент
            return current->data;
        }
        current = current->next;
        // Продолжаем до тех пор, пока не вернемся к head списка
    } while (current != head);

    // Если элемент не найден, возвращаем nullptr
    return nullptr;
}

// Метод для вывода всех элементов списка
void CircularLinkedList::displayAll() const {
    if (!head) {
        // Если список пуст
        std::cout << "The list is empty." << std::endl;
        return;
    }

    Node* current = head;
    do {
        // Выводим данные каждого элемента
        current->data->display();
        current = current->next;
        // Повторяем, пока не вернемся к head списка
    } while (current != head);
}
