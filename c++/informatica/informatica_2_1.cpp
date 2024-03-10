/*
Задание №2.

Написать функцию, которая выводит все цифры последовательности до k – ой. 
Использовать функцию, определяющую количество цифр в числе Count_Pos (number) 
(см пример дальше по тексту).


Последовательность 1001111112211331…98899999, в которой выписаны подряд все двузначные числа и числа наоборот. 
Значение k задается от 1 до 360.
*/

#include <iostream>
#include <string>

// Функция для подсчета количества цифр в числе
int Count_Pos(int number) {
    int count = 0;
    while(number != 0) {
        number /= 10;
        ++count;
    }
    return count;
}

// Функция для вывода последовательности
void print_sequence(int k) {
    std::string sequence = "";
    for(int i = 10; i < 100; ++i) {
        sequence += std::to_string(i);
        sequence += std::to_string(i % 10) + std::to_string(i / 10);
    }

    for(int i = 0; i < k; ++i) {
        std::cout << sequence[i];
    }
}

int main() {
    int k;
    std::cout << "Введите значение k: ";
    std::cin >> k;

    print_sequence(k);

    return 0;
}
