#include "generate_data.h"
#include <cstdlib>
#include <ctime>

/**
 * @brief Генерирует вектор случайных целых чисел заданного размера.
 *
 * Эта функция создает вектор, содержащий случайные целые числа в диапазоне от 0 до 999.
 *
 * @param size Количество элементов в векторе.
 * @return std::vector<int> Вектор, содержащий сгенерированные случайные целые числа.
 */
std::vector<int> generate_data(int size) {
    std::vector<int> data(size);
    for (int i = 0; i < size; ++i) {
        data[i] = std::rand() % 1000;
    }
    return data;
}
