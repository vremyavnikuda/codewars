/*
Даны три различных числа. Вывести их в порядке убывания.
*/

#include <iostream>

/*
Функция с условным оператором для вывода чисел в порядке убывания.
Она сравнивает три числа и выводит их в порядке убывания, используя
вложенные условные операторы if-else.

Тут даже комментировать стремно)
*/
void descending_order_with_if(int a, int b, int c)
{
    if (a >= b && a >= c)
    {
        if (b >= c)
        {
            using namespace std;
            std::cout << a << " " << b << " " << c << std::endl;
        }
        else
        {
            std::cout << a << " " << c << " " << b << std::endl;
        }
    }
    else if (b >= a && b >= c)
    {
        if (a >= c)
        {
            std::cout << b << " " << a << " " << c << std::endl;
        }
        else
        {
            std::cout << b << " " << c << " " << a << std::endl;
        }
    }
    else
    {
        if (a >= b)
        {
            std::cout << c << " " << a << " " << b << std::endl;
        }
        else
        {
            std::cout << c << " " << b << " " << a << std::endl;
        }
    }
}

/*
Функция с тернарной операцией для вывода чисел в порядке убывания.
Она использует тернарные операторы для определения максимального,
минимального и среднего чисел, а затем выводит их в порядке убывания.
*/
void descending_order_with_ternary(int a, int b, int c)
{
    int max_num = (a >= b && a >= c) ? a : ((b >= c) ? b : c);
    int min_num = (a <= b && a <= c) ? a : ((b <= c) ? b : c); // Исправлено условие для определения минимального числа
    int mid_num = a + b + c - max_num - min_num;
    std::cout << max_num << " " << mid_num << " " << min_num << std::endl;
}

/*
Основная функция программы.
Она запрашивает у пользователя три различных числа,
а затем вызывает обе функции для вывода чисел в порядке убывания.
*/
int main()
{
    int num1, num2, num3;
    std::cout << "num1: ";
    std::cin >> num1;
    std::cout << "num2: ";
    std::cin >> num2;
    std::cout << "num3: ";
    std::cin >> num3;

    std::cout << "descending_order_with_if: ";
    descending_order_with_if(num1, num2, num3);

    std::cout << "\ndescending_order_with_ternary: ";
    descending_order_with_ternary(num1, num2, num3);

    return 0;
}
