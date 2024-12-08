#ifndef LINKEDLIST_H
#define LINKEDLIST_H



template <typename T>
struct Node {
    T data;
    Node* next;

    Node(T val);
};

template <typename T>
class LinkedList {
private:
    Node<T>* head;

public:
    LinkedList();
    ~LinkedList();

    void insertOrdered(const T& value);
    void insertAt(int index, const T& value);
    void display() const;

private:
    // Метод для проверки на дублирование
    bool contains(const T& value) const;
};
#include "LinkedList.cpp"
#endif
