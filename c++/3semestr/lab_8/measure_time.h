#ifndef MEASURE_TIME_H
#define MEASURE_TIME_H

#include <chrono>
#include <string>
#include <functional>
#include <iostream>

/**
 * @brief Функция для измерения времени выполнения заданной операции.
 *
 * Эта функция измеряет время, необходимое для выполнения переданной функции func,
 * обрабатывает исключения, которые могут быть выброшены во время ее выполнения,
 * и выводит продолжительность операции в микросекундах.
 *
 * @tparam Func Тип функции, которая будет измеряться.
 * @param func Функция, время выполнения которой измеряется.
 * @param operation_name Имя операции, используемое для логирования.
 *
 * @return void Функция не возвращает значение.
 */
template<typename Func>
void measure_time(Func func, const std::string &operation_name) {
    auto start = std::chrono::high_resolution_clock::now();
    try {
        func();
    } catch (const std::exception &e) {
        std::cout << "exception_during " << operation_name << ": " << e.what() << std::endl;
    }
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
    std::cout << operation_name << " took " << duration << " microseconds." << std::endl;
}

#endif // MEASURE_TIME_H
