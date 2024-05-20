/*
Задание №1.Написать функцию, которая считывает целое k, за которым следует k целых чисел. Функция должна считывать только по одному значению в операторе ввода. При решении задачи использовать цикл for.
 Найти наименьшее значение во вводимой последовательности чисел.


Задание №2.
 Написать функцию, которая выводит все цифры последовательности до k – ой. Использовать функцию, определяющую количество цифр в числе Count_Pos (number) (см пример дальше по тексту). При решении задачи использовать цикл while или do / while.
- Последовательность 182764125216343…, в которой выписаны подряд кубы всех натуральных чисел.
*/

#include <iostream>
#include <climits>
#include <math.h>

// функция для нахождения наименьшего значения в последовательности чисел с использованием цикла for
int find_min_with_for()
{
    int num, min_num;
    int count;
    std::cout << "length num find_min_with_for: ";
    std::cin >> count;
    min_num = count;
    for (int i = 1; i <= count; i++)
    {
        std::cout << "enter number find_min_with_for" << i << ": ";
        std::cin >> num;
        if (num < min_num)
        {
            min_num = num;
        }
    }
    std::cout << "Min number is: ";
    return min_num;
}

// функция для определения количества цифр в числе
int Count_Pos(long number)
{
    int count = 0;
    while (number != 0)
    {
        number /= 10;
        count++;
    }
    return count;
}
void PrintCubesToK(int k)
{

    std::string stroka = ""; // склад для кубиков циферок
    int n = 1;               // нужны кубы натуральных чесел, 0 - не натуральное 🙁

    while (stroka.length() < k)
    {
        long cube = pow(n, 3);

        stroka += std::to_string(cube);
    }
    std::cout << stroka.substr(0) << std::endl;
}

int main()
{
    // Номер цифры в последовательности

    std::cout << "Number I: Find min number: " << std::endl;
    std::cout << find_min_with_for() << std::endl;
    std::cout << std::endl;
    int k;
    std::cout << "Number II: Cuby : " << std::endl;
    std::cout << "Enter k: ";
    std::cin >> k;

    PrintCubesToK(k);

    return 0;
}
