#include <iostream>
#include "measure_time.h"
#include "generate_data.h"
#include "list_operations.h"
#include "multimap_operations.h"

/**
 * @brief Основная функция программы.
 *
 * Инициализирует генерацию случайных данных, выполняет операции добавления, поиска, сортировки и удаления для std::list и std::multimap, используя функцию measure_time для измерения времени выполнения каждой операции.
 *
 * @return Возвращает 0 после завершения выполнения программы.
 */
int main() {
    std::srand(static_cast<unsigned>(std::time(nullptr)));

    const int data_size = 100000;
    std::vector<int> data = generate_data(data_size);

    // std::list dev
    std::list<int> myList;

    measure_time([&] { list_addition(myList, data); }, "Add to std::list");
    measure_time([&] { list_search(myList); }, "Search in std::list");
    measure_time([&] { list_sort(myList); }, "Sort std::list");
    measure_time([&] { list_deletion(myList); }, "Delete from std::list");

    // std::multimap dev
    std::multimap<int, int> myMap;

    measure_time([&] { multimap_addition(myMap, data); }, "Add to std::multimap");
    measure_time([&] { multimap_search(myMap); }, "Search in std::multimap");
    measure_time([&] { multimap_deletion(myMap); }, "Delete from std::multimap");

    return 0;
}
