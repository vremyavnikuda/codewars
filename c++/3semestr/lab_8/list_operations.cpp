#include "list_operations.h"
#include <algorithm>
#include "ListException.h"

/**
 * @brief Добавляет элементы из вектора в список.
 *
 * Функция добавляет все элементы из переданного вектора в конец списка.
 *
 * @param myList Ссылка на список, в который будут добавлены элементы.
 * @param data Константная ссылка на вектор, содержащий элементы для добавления.
 */
void list_addition(std::list<int> &myList, const std::vector<int> &data) {
    for (int value: data) {
        myList.push_back(value);
    }
}

/**
 * @brief Удаляет первый элемент из списка.
 *
 * Функция удаляет первый элемент списка. Если список пуст, генерирует исключение ListException.
 *
 * @param myList Ссылка на список, из которого будет удален первый элемент.
 * @throws ListException Если список пуст.
 */
void list_deletion(std::list<int> &myList) {
    if (myList.empty()) {
        throw ListException();
    }
    myList.erase(myList.begin());
}

/**
 * @brief Ищет элемент со значением 500 в списке.
 *
 * Функция ищет в списке элемент со значением 500. Если такой элемент не найден, генерирует исключение ListException.
 *
 * @param myList Константная ссылка на список, в котором будет производиться поиск.
 * @throws ListException Если элемент со значением 500 не найден.
 */
void list_search(const std::list<int> &myList) {
    auto it = std::find_if(myList.begin(), myList.end(), [](int value) { return value == 500; });
    if (it == myList.end()) {
        throw ListException();
    }
}

/**
 * @brief Сортирует список.
 *
 * Функция сортирует элементы списка в порядке возрастания.
 *
 * @param myList Ссылка на список, который будет отсортирован.
 */
void list_sort(std::list<int> &myList) {
    myList.sort();
}
