#include <iostream>
#include "LinkedList.h"

int main() {
    LinkedList<int> list;

    // Вставляем элементы с упорядочиванием
    list.insertOrdered(5);
    list.insertOrdered(2);
    list.insertOrdered(8);
    list.insertOrdered(3);

    std::cout << "list_after_ordered_insertions: ";
    list.display();

    // Попытка вставить дубликат
    // Дублирующий элемент
    list.insertOrdered(5);
    list.display();

    // Вставляем элемент по индексу
    list.insertAt(2, 10);
    std::cout << "list_after_inserting_10_at_index_2: ";
    list.display();

    return 0;
}
