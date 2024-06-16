#include <limits.h>
#include <stdio.h>
// Рекурсивная функция для нахождения наибольшего отрицательного значения
int findMaxNegative(int k)
{
    // Базовый случай ,если k==0 ,возвращаем минимальное значение целого числа
    if (k == 0)
    {
        return INT_MIN;
    }

    int num;
    printf("Введите число:");
    scanf("%d", &num);

    // Рекурсивный вызов функции для оставшихся чисел (k-1)
    int maxNegative = findMaxNegative(k - 1);
    // Если текущее число отрицательное и больше текущего максимального отрицательного числа
    if (num < 0 && num > maxNegative)
    {
        return num;
    }
    return maxNegative;
}

int main()
{
    int k;
    printf("Введите количество чисел: ");
    scanf("%d", &k);

    int maxNegative = findMaxNegative(k);

    if (maxNegative == INT_MIN)
    {
        printf("В последовательности нет отрицательных чисел.\n");
    }
    else
    {
        printf("Наибольшее из отрицательных чисел: %d\n", maxNegative);
    }
    return 0;
}