#include <iostream>
#include <cmath>

// Задание №1: Найти наибольшее из отрицательных значений во вводимой последовательности чисел
int findMaxNegative()
{
    int k;
    std::cout << "Enter the number of integers (k): ";
    std::cin >> k;

    int maxNegative = INT_MIN; // Инициализируем максимальное отрицательное значение

    for (int i = 0; i < k; ++i)
    {
        int num;
        std::cout << "Enter integer " << i + 1 << ": ";
        std::cin >> num;

        if (num < 0 && num > maxNegative)
        {
            maxNegative = num;
        }
    }

    return maxNegative;
}

// Функция для определения количества цифр в числе
int countDigits(int number)
{
    if (number == 0)
    {
        return 1; // Отдельно обрабатываем случай с числом 0
    }

    int digits = 0;
    while (number != 0)
    {
        number /= 10;
        ++digits;
    }
    return digits;
}

// Функция для вывода всех цифр последовательности до k-ой
void printSequenceDigits(int k)
{
    int count = 0;   // Счетчик выводимых цифр
    int number = 10; // Начинаем с первого двузначного числа

    std::cout << "Sequence digits: ";

    while (count < k)
    {
        int digits = countDigits(number);

        for (int i = 0; i < digits; ++i)
        {
            std::cout << number / static_cast<int>(std::pow(10, digits - i - 1)) % 10 << " ";
            ++count;
            if (count >= k)
            {
                break;
            }
        }

        if (count >= k)
        {
            break;
        }

        // Добавляем зеркальное отражение числа в последовательность
        int reverseNumber = 0;
        int temp = number;
        while (temp != 0)
        {
            reverseNumber = reverseNumber * 10 + temp % 10;
            temp /= 10;
        }
        number = reverseNumber;
    }

    std::cout << std::endl;
}
int main()
{
    // Задание №1
    int maxNegative = findMaxNegative();
    if (maxNegative != INT_MIN)
    {
        std::cout << "Maximum negative integer: " << maxNegative << std::endl;
    }
    else
    {
        std::cout << "No negative integers were entered." << std::endl;
    }

    // Задание №2
    int k;
    std::cout << "Enter k: ";
    std::cin >> k;

    printSequenceDigits(k);

    return 0;
}
