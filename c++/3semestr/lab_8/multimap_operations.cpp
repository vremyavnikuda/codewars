#include "multimap_operations.h"
#include "MapException.h"

/**
 * @brief Добавляет элементы из вектора в multimap.
 *
 * Функция добавляет пары {value, value} для каждого value из вектора data в multimap myMap.
 *
 * @param myMap Ссылка на multimap, в который будут добавлены элементы.
 * @param data Константная ссылка на вектор, содержащий элементы для добавления.
 */
void multimap_addition(std::multimap<int, int> &myMap, const std::vector<int> &data) {
    for (int value: data) {
        myMap.insert({value, value});
    }
}

/**
 * @brief Удаляет элементы с ключом 500 из multimap.
 *
 * Функция ищет и удаляет элементы с ключом 500 из multimap myMap. Если элементы не найдены, генерирует исключение MapException.
 *
 * @param myMap Ссылка на multimap, из которого будут удалены элементы.
 * @throws MapException Если элементы с ключом 500 не найдены.
 */
void multimap_deletion(std::multimap<int, int> &myMap) {
    auto range = myMap.equal_range(500);
    if (range.first == range.second) {
        throw MapException();
    }
    myMap.erase(range.first);
}

/**
 * @brief Ищет элементы с ключом 500 в multimap.
 *
 * Функция ищет элементы с ключом 500 в multimap myMap. Если элементы не найдены, генерирует исключение MapException.
 *
 * @param myMap Константная ссылка на multimap, в котором производится поиск.
 * @throws MapException Если элементы с ключом 500 не найдены.
 */
void multimap_search(const std::multimap<int, int> &myMap) {
    auto range = myMap.equal_range(500);
    if (range.first == range.second) {
        throw MapException();
    }
}
