#include <iostream>
#include <limits>

/*
Объяснение:

Функция findMaxNegative:
Инициализирует переменную maxNegative минимальным значением типа int и булевую переменную foundNegative, указывающую, найдено ли отрицательное число.
Использует цикл for для ввода k чисел.
Пропускает неотрицательные числа с помощью оператора continue.
Обновляет maxNegative, если текущее отрицательное число больше текущего значения maxNegative.

Функция main:
Считывает значение k.
Проверяет, что k положительное.
Вызывает findMaxNegative и выводит результат. Если отрицательных чисел не найдено, сообщает об этом.
Программа завершает выполнение, если ввод некорректен (например,k≤0).
*/


// Функция для считывания k чисел и нахождения наибольшего отрицательного числа
int findMaxNegative(int k)
{
    // Инициализация минимальным значением int
    int maxNegative = std::numeric_limits<int>::min();
    // Флаг для проверки наличия отрицательного числа
    bool foundNegative = false;

    for (int i = 0; i < k; ++i)
    {
        int num;
        std::cout << "Введите число " << (i + 1) << ": ";
        std::cin >> num;
        if (num >= 0)
        {
            // Пропускаем неотрицательные числа
            continue;
        }
        if (!foundNegative || num > maxNegative)
        {
            maxNegative = num;
            foundNegative = true;
        }
    }
    if (!foundNegative)
    {
        std::cout << "В последовательности нет отрицательных чисел.\n";
        // Возвращаем минимальное значение int
        return std::numeric_limits<int>::min();
    }
    return maxNegative;
}

int main()
{
    int k;
    std::cout << "Введите количество чисел (k): ";
    std::cin >> k;
    if (k <= 0)
    {
        std::cout << "Количество чисел должно быть положительным.\n";
        // Завершение программы с кодом ошибки
        return 1; 
    }
    int maxNegative = findMaxNegative(k);
    if (maxNegative != std::numeric_limits<int>::min())
    {
        std::cout << "Наибольшее из отрицательных чисел: " << maxNegative << "\n";
    }
    return 0;
}
