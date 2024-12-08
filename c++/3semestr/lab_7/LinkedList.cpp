#include <iostream>
#include <stdexcept>
#include "LinkedList.h"

// Реализация конструктора узла
template <typename T>
Node<T>::Node(T val) : data(val), next(nullptr) {}

// Конструктор класса LinkedList
template <typename T>
LinkedList<T>::LinkedList() : head(nullptr) {}

// Деструктор класса LinkedList
template <typename T>
LinkedList<T>::~LinkedList() {
    Node<T>* current = head;
    while (current) {
        Node<T>* temp = current;
        current = current->next;
        delete temp;
    }
}

// Метод для проверки наличия элемента в списке
template <typename T>
bool LinkedList<T>::contains(const T& value) const {
    Node<T>* current = head;
    while (current) {
        if (current->data == value) {
            // Элемент найден, возвращаем true
            return true;
        }
        current = current->next;
    }
    // Элемент не найден
    return false;
}

// Вставка элемента с сохранением упорядоченности с проверкой на дублирование
template <typename T>
void LinkedList<T>::insertOrdered(const T& value) {
    // Проверяем, не существует ли уже такой элемент в списке
    if (contains(value)) {
        std::cout << "element " << value << " already_Exists_In_The_List_Insertion_Omitted." << std::endl;
        return;
    }

    Node<T>* newNode = new Node<T>(value);
    if (!head || head->data > value) {
        newNode->next = head;
        head = newNode;
    } else {
        Node<T>* current = head;
        while (current->next && current->next->data <= value) {
            current = current->next;
        }
        newNode->next = current->next;
        current->next = newNode;
    }
}

// Вставка элемента по индексу
template <typename T>
void LinkedList<T>::insertAt(int index, const T& value) {
    if (index < 0) throw std::out_of_range("index_Out_Of_Range");

    Node<T>* newNode = new Node<T>(value);
    if (index == 0) {
        newNode->next = head;
        head = newNode;
    } else {
        Node<T>* current = head;
        for (int i = 0; i < index - 1; ++i) {
            if (!current) throw std::out_of_range("index_Out_Of_Range");
            current = current->next;
        }
        newNode->next = current->next;
        current->next = newNode;
    }
}

// Вывод всех элементов списка
template <typename T>
void LinkedList<T>::display() const {
    Node<T>* current = head;
    while (current) {
        std::cout << current->data << " ";
        current = current->next;
    }
    std::cout << std::endl;
}
