/*
Тема №3 Массивы целых чисел.

Дан массив целых чисел. Вывести те из них, индексы которых являются числами Фибоначчи.
*/

#include <iostream>
#include <cmath>
#include <cstdlib> // Для функции rand()
#include <ctime>   // Для функции srand()
using namespace std;

bool isPerfectSquare(int x)
{
    int s = sqrt(x);
    return (s * s == x);
}

bool isFibonacci(int n)
{
    return isPerfectSquare(5 * n * n + 4) || isPerfectSquare(5 * n * n - 4);
}

int main()
{
    int k;
    cout << "Enter size of an array: ";
    cin >> k;

    // Выделение памяти для массива с помощью malloc
    int *arr = (int *)malloc(k * sizeof(int));

    srand(time(NULL)); // Задание seed для генератора случайных чисел

    for (int i = 0; i < k; i++)
    {
        arr[i] = rand() % 10; // Заполнение массива случайными целыми числами от 0 до 10
    }

    cout << "Inputed array:" << endl;
    for (int n = 0; n < k; n++)
    {
        cout << arr[n] << " | ";
    }
    cout << endl;

    cout << "Elements with Fibonacci indexes: " << endl;
    for (int i = 0; i < k; ++i)
    {
        if (isFibonacci(i))
            cout << arr[i] << " | ";
    }
    cout << endl;

    cout << "Indexes: " << endl;
    for (int j = 0; j < k; j++)
    {
        if (isFibonacci(j))
            cout << j << " | ";
    }
    cout << endl;

    // Освобождение памяти, выделенной для массива
    free(arr);

    return 0;
}
