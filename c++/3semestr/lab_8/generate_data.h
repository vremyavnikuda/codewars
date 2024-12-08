#ifndef GENERATE_DATA_H
#define GENERATE_DATA_H

#include <vector>

/**
 * @brief Генерирует вектор случайных целых чисел заданного размера.
 *
 * Функция генерирует вектор, содержащий случайные целые числа, количество которых определяется параметром size.
 *
 * @param size Количество элементов, которые нужно сгенерировать.
 * @return std::vector<int> Вектор, содержащий сгенерированные случайные целые числа.
 */
std::vector<int> generate_data(int size);

#endif // GENERATE_DATA_H
