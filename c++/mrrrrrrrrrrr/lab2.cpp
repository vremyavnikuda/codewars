/*lab2.cpp
Задание №1. При решении задачи использовать три типа циклов (три реализации функции).
- Найти наименьшее значение во вводимой последовательности чисел.

Задание №2.
Написать функцию, которая выводит все цифры последовательности до k – ой. Использовать функцию, определяющую количество цифр в числе Count_Pos (number) (см пример дальше по тексту).
- Последовательность 182764125216343…, в которой выписаны подряд кубы всех натуральных чисел.
*/

#include <iostream>
// Для использования INT_MAX
#include <climits>
#include <math.h>

// функция для нахождения наименьшего значения в последовательности чисел с использованием цикла for
// TODO: тоже самое что и @find_min_with_while
int find_min_with_for()
{
    int num, min_num = INT_MAX;
    int count;
    std::cout << "length num find_min_with_for: ";
    std::cin >> count;
    for (int i = 0; i < count; i++)
    {
        std::cout << "enter number find_min_with_for" << i + 1 << ": ";
        std::cin >> num;
        if (num < min_num)
        {
            min_num = num;
        }
    }
    return min_num;
}

// функция для нахождения наименьшего значения в последовательности чисел с использованием цикла while
int find_min_with_while()
{
    int num, min_num = INT_MAX;
    int count, i = 0;
    std::cout << "length num find_min_with_while: ";
    std::cin >> count;
    // ебашим до тех пор пока i меньше чем count
    while (i < count)
    {
        std::cout << "enter number find_min_with_while" << i + 1 << ": ";
        // вводим числа -> перебираем числа
        std::cin >> num;
        if (num < min_num)
        {
            min_num = num;
        }
        i++;
    }
    // ретерн рэззззззззаааааааааааааааааллллллллттт kekw
    return min_num;
}

// функция для нахождения наименьшего значения в последовательности чисел с использованием цикла do-while
int find_min_with_do_while()
{
    int num, min_num = INT_MAX;
    // cont ==0 ,ну эт понятно
    int count, i = 0;
    std::cout << "length find_min_with_do_while: ";
    std::cin >> count;
    // дрочим do while до тех пор пока делится на 10 м-математика
    do
    {
        std::cout << "enter number find_min_with_do_while " << i + 1 << ": ";
        std::cin >> num;
        if (num < min_num)
        {
            min_num = num;
        }
        i++;
        // тут как у девочек редфлаг 🚩
    } while (i < count);
    // на выходе выплевываем min_num =`<
    return min_num;
}

// функция для определения количества цифр в числе
int count_digits(int number)
{
    int count = 0;
    // таже залупа только по диагонали 🤮
    while (number != 0)
    {
        number /= 10;
        count++;
    }
    // ретерн каааааааааааууууууууууууууунннннннннннннннтттттттттттттттт ,,/,,
    return count;
}

// функция для вывода всех цифр последовательности до k-ой
void print_sequence_digits(int k)
{
    // начинаем с первого натурального числа
    int n = 1;
    int count = 0;
    int digit_count = 0;

    // думаешь самое страшное штаны обосраться ?????? хуй  >>> if в for в while  это просто отвал пизды
    // while -> выполняется до тех пор, пока не будет достигнут заданный лимит k
    while (count < k)
    {
        int cube = n * n * n;
        digit_count = count_digits(cube);

        // проходит по каждой цифре куба, начиная с старшего разряда
        for (int i = 0; i < digit_count; i++)
        {
            if (count == k)
            {
                break;
            }
            int digit = (cube / static_cast<int>(std::pow(10, digit_count - i - 1))) % 10;
            std::cout << digit << " ";
            // count достигнет значения k -> ливаем с цикла
            count++;
        }
        n++;
    }
}

int main()
{
    // Номер цифры в последовательности
    int k;
    std::cout << "Enter number k: ";
    std::cin >> k;
    // выводит все цифры последовательности до k-ой
    std::cout << "Sequence digits to " << k << " : ";
    print_sequence_digits(k);
    std::cout << std::endl;

    std::cout << "result find_min_with_for() -> for: min number: " << find_min_with_for() << std::endl;
    std::cout << "result find_min_with_while() -> while: min number: " << find_min_with_while() << std::endl;
    std::cout << "result find_min_with_do_while -> do-while: min number: " << find_min_with_do_while() << std::endl;
    return 0;
}
