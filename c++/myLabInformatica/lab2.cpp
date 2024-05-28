#include <iostream>
// Функция для определения количества цифр в числе
int Count_Pos(int number)
{
    int count = 0;
    while (number != 0)
    {
        number /= 10;
        ++count;
    }
    return count;
}
// Функция для поиска максимального отрицательного числа в последовательности чисел
int findMaxNegative(int k)
{
    // Инициализируем переменную для максимального отрицательного значения как наименьшее возможное целое число
    int maxNegative = INT_MIN;
    int num;

    for (int i = 0; i < k; ++i)
    {
        // Считываем одно число из ввода
        std::cin >> num;
        // Проверяем, является ли считанное число отрицательным и больше текущего максимального отрицательного значения
        if (num < 0 && num > maxNegative)
        {
            // Обновляем максимальное отрицательное значение
            maxNegative = num;
        }
    }
    // Возвращаем найденное максимальное отрицательное значение
    return maxNegative;
}

// Функция для вывода всех цифр последовательности до k-й
void printSequenceDigits(int k)
{
    int number = 10; // Начинаем с двузначного числа
    int count = 0;

    while (count < k)
    {
        // Определяем количество цифр в числе
        int numDigits = Count_Pos(number);
        int divisor = 1;
        for (int i = 1; i < numDigits; ++i)
        {
            // Вычисляем делитель для извлечения цифр числа
            divisor *= 10;
        }

        // Выводим все цифры числа
        while (divisor != 0 && count < k)
        {
            std::cout << number / divisor << " ";
            number %= divisor;
            divisor /= 10;
            ++count;
        }

        // Если мы достигли k-й цифры, выходим из цикла
        if (count >= k)
        {
            break;
        }

        // Переходим к следующему числу
        number++;

        // Если достигли числа 99, переходим к числу 10
        if (number == 100)
        {
            number = 10;
        }
    }
}

int main()
{
    int k;
    std::cout << "Enter the number of integers: ";
    std::cin >> k;
    if (k <= 0)
    {
        std::cout << "The number of numbers must be positive.\n";
        // Завершаем программу с ошибкой, если введено некорректное количество чисел
        return 1;
    }

    std::cout << "Enter " << k << " integers:\n";
    // Вызываем функцию для поиска максимального отрицательного числа
    int maxNegative = findMaxNegative(k);
    if (maxNegative == INT_MIN)
    {
        std::cout << "There are no negative numbers.\n";
    }
    else
    {
        std::cout << "The largest negative number: " << maxNegative << std::endl;
    }

    std::cout << "Digits of the sequence up to " << k << ":\n";
    // Вызываем функцию для вывода цифр последовательности
    printSequenceDigits(k);
    std::cout << std::endl;

    return 0;
}
