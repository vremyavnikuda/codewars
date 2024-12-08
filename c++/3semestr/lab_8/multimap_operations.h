#ifndef MULTIMAP_OPERATIONS_H
#define MULTIMAP_OPERATIONS_H

#include <map>
#include <vector>

/**
 * @brief Добавляет элементы в multimap.
 *
 * Эта функция добавляет пары {value, value} для каждого value из вектора data в multimap myMap.
 *
 * @param myMap Ссылка на multimap, в который будут добавлены элементы.
 * @param data Константная ссылка на вектор, содержащий элементы для добавления.
 */
void multimap_addition(std::multimap<int, int> &myMap, const std::vector<int> &data);

/**
 * @brief Удаляет элементы с ключом 500 из multimap.
 *
 * Эта функция удаляет все элементы с ключом 500 из multimap myMap. Если элементы не найдены, выбрасывает исключение MapException.
 *
 * @param myMap Ссылка на multimap, из которого будут удалены элементы.
 * @throws MapException Если элементы с ключом 500 не найдены.
 */
void multimap_deletion(std::multimap<int, int> &myMap);

/**
 * @brief Ищет элементы с ключом 500 в multimap.
 *
 * Эта функция ищет элементы с ключом 500 в multimap myMap. Если элементы не найдены, выбрасывает исключение MapException.
 *
 * @param myMap Константная ссылка на multimap, в котором производится поиск.
 * @throws MapException Если элементы с ключом 500 не найдены.
 */
void multimap_search(const std::multimap<int, int> &myMap);

#endif // MULTIMAP_OPERATIONS_H
