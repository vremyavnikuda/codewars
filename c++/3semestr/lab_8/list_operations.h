#ifndef LIST_OPERATIONS_H
#define LIST_OPERATIONS_H

#include <list>
#include <vector>

/**
 * @brief Добавляет элементы из вектора в список.
 *
 * Эта функция добавляет все элементы из вектора data в список myList.
 *
 * @param myList Ссылка на список, в который будут добавлены элементы.
 * @param data Константная ссылка на вектор, содержащий элементы для добавления.
 */
void list_addition(std::list<int> &myList, const std::vector<int> &data);

/**
 * @brief Удаляет элемент из списка.
 *
 * Эта функция удаляет первый элемент из списка myList. Если список пуст, генерирует исключение ListException.
 *
 * @param myList Ссылка на список, из которого будет удален элемент.
 * @throws ListException Если список пуст.
 */
void list_deletion(std::list<int> &myList);

/**
 * @brief Ищет элемент в списке.
 *
 * Эта функция ищет элемент со значением 500 в списке myList. Если элемент не найден, генерирует исключение ListException.
 *
 * @param myList Константная ссылка на список, в котором производится поиск.
 * @throws ListException Если элемент не найден.
 */
void list_search(const std::list<int> &myList);

/**
 * @brief Сортирует список.
 *
 * Эта функция сортирует элементы списка myList в порядке возрастания.
 *
 * @param myList Ссылка на список, который будет отсортирован.
 */
void list_sort(std::list<int> &myList);

#endif // LIST_OPERATIONS_H
