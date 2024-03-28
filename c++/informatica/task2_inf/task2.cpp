#include <iostream>
#include <climits>

void readNumbers(int *numbers, int k)
{
    for (int i = 0; i < k; ++i)
    {
        std::cin >> numbers[i];
    }
}

// Функция для поиска наибольшего отрицательного числа с использованием цикла for
int findMaxNegative(int *numbers, int k)
{
    int maxNegative = INT_MIN; 
    for (int i = 0; i < k; i++)
    {
        int num = numbers[i];
        if (num < 0 && num > maxNegative)
        {
            maxNegative = num; 
        }
    }
    return maxNegative != INT_MIN ? maxNegative : 0; 
}

int findMaxNegativeWhile(int *numbers, int k)
{
    int maxNegative = INT_MIN; 
    int i = 0;
    while (i < k)
    {
        int num = numbers[i];
        if (num < 0 && num > maxNegative)
        {
            maxNegative = num; 
        }
        i++;
    }
    return maxNegative != INT_MIN ? maxNegative : 0; 
}

// Функция для поиска максимального отрицательного числа с использованием цикла do-while
int findMaxNegativeDoWhile(int *numbers, int k)
{
    int maxNegative = INT_MIN; 
    int i = 0;
    do
    {
        int num = numbers[i];
        if (num < 0 && num > maxNegative)
        {
            maxNegative = num; 
        }
        i++;
    } while (i < k);
    return maxNegative != INT_MIN ? maxNegative : 0; // Если нет отрицательных чисел, возвращаем 0
}

int main()
{
    int k;
    std::cin >> k;             
    int *numbers = new int[k]; 
    readNumbers(numbers, k);   

    int maxNegativeFor = findMaxNegative(numbers, k); 
    int maxNegativeWhile = findMaxNegativeWhile(numbers, k);
    int maxNegativeDoWhile = findMaxNegativeDoWhile(numbers, k);
    
    // Выводим результаты
    std::cout << "for: " << maxNegativeFor << std::endl;
    std::cout << "while: " << maxNegativeWhile << std::endl;
    std::cout << "while: " << maxNegativeDoWhile << std::endl;
    
    delete[] numbers; 
    return 0;
}