#include <iostream>
#include <cmath>
#include <cstdlib>
#include <ctime>

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
    std::cout << "Enter size of an array: ";
    std::cin >> k;

    // Выделение памяти для массива с помощью malloc
    int *arr = (int *)malloc(k * sizeof(int));

    std::cout << "Enter elements of an array:" << std::endl;
    for (int i = 0; i < k; i++)
    {
        std::cout << "Enter element " << i + 1 << ": ";
        std::cin >> arr[i];
    }

    std::cout << "Inputed array:" << std::endl;
    for (int n = 0; n < k; n++)
    {
        std::cout << arr[n] << " | ";
    }
    std::cout << std::endl;

    std::cout << "Elements with Fibonacci indexes: " << std::endl;
    for (int i = 0; i < k; ++i)
    {
        if (isFibonacci(i))
            std::cout << arr[i] << " | ";
    }
    std::cout << std::endl;

    std::cout << "Indexes: " << std::endl;
    for (int j = 0; j < k; j++)
    {
        if (isFibonacci(j))
            std::cout << j << " | ";
    }
    std::cout << std::endl;

    // Освобождение памяти, выделенной для массива
    free(arr);

    return 0;
}
