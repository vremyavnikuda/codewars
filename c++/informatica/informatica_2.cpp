/*
Задание №1. 

При решении задачи использовать три типа циклов (три реализации функции).

Написать функцию, которая считывает целое k, за которым следует k целых чисел. 
Функция должна считывать только по одному значению в операторе ввода.
*/

//Использование цикла for
#include <iostream>
#include <climits>

int max_negative_for() {
    int k, num;
    int max_negative = INT_MIN;

    std::cout << "Введите количество чисел: ";
    std::cin >> k;

    for(int i = 0; i < k; i++) {
        std::cout << "Введите число: ";
        std::cin >> num;
        if(num < 0 && num > max_negative) {
            max_negative = num;
        }
    }

    return max_negative == INT_MIN ? 0 : max_negative;
}

// Использование цикла while
int max_negative_while() {
    int k, num;
    int max_negative = INT_MIN;

    std::cout << "Введите количество чисел: ";
    std::cin >> k;

    int i = 0;
    while(i < k) {
        std::cout << "Введите число: ";
        std::cin >> num;
        if(num < 0 && num > max_negative) {
            max_negative = num;
        }
        i++;
    }

    return max_negative == INT_MIN ? 0 : max_negative;
}

//Использование цикла do-while
int max_negative_do_while() {
    int k, num;
    int max_negative = INT_MIN;

    std::cout << "Введите количество чисел: ";
    std::cin >> k;

    int i = 0;
    do {
        std::cout << "Введите число: ";
        std::cin >> num;
        if(num < 0 && num > max_negative) {
            max_negative = num;
        }
        i++;
    } while(i < k);

    return max_negative == INT_MIN ? 0 : max_negative;
}
