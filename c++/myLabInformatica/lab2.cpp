#include <iostream>
#include <string>
#include <climits>

// Задание №1: Найти наибольшее из отрицательных значений во вводимой последовательности чисел
int findMaxNegative()
{
    int k;
    std::cout << "Введите количество чисел (k): ";
    std::cin >> k;
    // Инициализируем максимальное отрицательное значение
    int maxNegative = INT_MIN;
    for (int i = 0; i < k; ++i)
    {
        int num;
        std::cout << "Введите целое число " << i + 1 << ": ";
        std::cin >> num;
        // Обновляем максимальное отрицательное значение, если текущее число отрицательное и больше текущего максимума
        if (num < 0 && num > maxNegative)
        {
            maxNegative = num;
        }
    }
    return maxNegative;
}
// Функция для подсчета количества символов в строке
int countDigits(const std::string &str)
{
    int cnt = 0;
    // Проходим по всем символам строки и считаем их количество
    for (char ch : str)
    {
        cnt++;
    }
    return cnt;
}
// Функция для генерации последовательности двузначных чисел и их зеркальных копий
std::string generateSequence()
{
    std::string sequence;
    // Генерируем последовательность из двузначных чисел и их зеркальных копий
    for (int number = 10; number < 100; ++number)
    {
        // Преобразуем число в строку
        std::string original = std::to_string(number);
        // Создаем зеркальную копию строки
        std::string reversed = std::string(original.rbegin(), original.rend());
        // Добавляем оригинальную строку и ее зеркальную копию в последовательность
        sequence += original + reversed;
    }
    return sequence;
}
// Функция для получения k-ой цифры в последовательности
char getKthDigit(const std::string &sequence, int k)
{
    // Возвращаем k-ую цифру (учитываем, что индексация начинается с 0)
    return sequence[k - 1];
}
int main()
{
    // Задание №1
    int maxNegative = findMaxNegative();
    if (maxNegative != INT_MIN)
    {
        std::cout << "Максимальное отрицательное число: " << maxNegative << std::endl;
    }
    else
    {
        std::cout << "Отрицательные числа не были введены." << std::endl;
    }
    // Задание №2
    std::string sequence = generateSequence();
    int k;
    std::cout << "Введите k (1 <= k <= 360): ";
    std::cin >> k;
    // Проверка на корректность введенного значения k
    if (k < 1 || k > 360)
    {
        std::cerr << "Некорректный ввод. k должно быть в диапазоне от 1 до 360." << std::endl;
        return 1;
    }
    // Вывод всей сгенерированной последовательности для проверки
    std::cout << generateSequence() << std::endl;
    // Получаем k-ую цифру
    char result = getKthDigit(sequence, k);
    std::cout << "k-ая цифра: " << result << std::endl;
    std::cout << "Общее количество цифр в последовательности: " << countDigits(sequence) << std::endl;
    return 0;
}