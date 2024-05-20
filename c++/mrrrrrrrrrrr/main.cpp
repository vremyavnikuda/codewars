#include <iostream>
#include <string>
#include <cctype>
#include <cmath>

bool isPerfectSquare(int x)
{
    int s = sqrt(x);
    return (s * s == x);
}

bool isFibonacci(int n)
{
    return isPerfectSquare(5 * n * n + 4) || isPerfectSquare(5 * n * n - 4);
}

void enteringOfAnArray(int *arr, int size)
{
    std::cout << "Enter elements of an array:" << std::endl;
    for (int i = 0; i < size; i++)
    {
        std::cout << "Enter element " << i + 1 << ": ";
        std::cin >> arr[i];
    }
}

void printArray(int *arr, int size)
{
    std::cout << "Inputed array:" << std::endl;
    for (int i = 0; i < size; i++)
    {
        std::cout << arr[i] << " | ";
    }
    std::cout << std::endl;
}

void printFibonacciElements(int *arr, int size)
{
    std::cout << "Elements with Fibonacci indexes: " << std::endl;
    for (int i = 0; i < size; i++)
    {
        if (isFibonacci(i))
        {
            std::cout << arr[i] << " | ";
        }
    }
    std::cout << std::endl;
}

void printFibonacciIndexes(int size)
{
    std::cout << "Indexes: " << std::endl;
    for (int i = 0; i < size; i++)
    {
        if (isFibonacci(i))
        {
            std::cout << i << " | ";
        }
    }
    std::cout << std::endl;
}

void bigBukvi(char *strochka)
{
    if (strochka == nullptr || *strochka == '\0')
        return;

    char FirstBukva = *strochka;
    bool FirstProideno = false; // флаг для определения что первый символ пройден

    for (char *sym = strochka; *sym != '0'; sym++)
    { // цикл для прохлождения по всему слову до последней буквы
        if (tolower(*sym) == tolower(FirstBukva))
        { // замена строчной на заглавную
            if (FirstProideno)
            {
                *sym = toupper(*sym);
            }
            else
            { // если предыдущее условие не выполняется, значит первый символ не пройден -> меняем флаг
                FirstProideno = true;
            }
        }
    }
}

void cubiki(int chislo)
{
    int *chi = new int[chislo];
    int *chiStartuem = chi;

    for (int i = 1; i <= chislo; i++)
    {
        *chi = pow(i, 3);
        chi++;
    }

    std::cout << "Cubed sequence: ";
    for (int *j = chiStartuem; j < chi; j++)
    {
        std::cout << *j << " ";
    }

    delete[] chiStartuem;
    std::cout << std::endl;
}

int main()
{
    int k;
    std::cout << "Enter size of an array: ";
    std::cin >> k;

    int *arr = new int[k];
    enteringOfAnArray(arr, k);

    std::cout << "_____________________________________________________________________________" << std::endl;

    std::cout << "Task 1:" << std::endl;
    printArray(arr, k);
    printFibonacciElements(arr, k);
    printFibonacciIndexes(k);

    std::cout << "_____________________________________________________________________________" << std::endl;

    std::cout << "Task 2:" << std::endl;
    const int MaxStrochechka = 100;
    char prinyato[MaxStrochechka];
    std::cout << "Enter the line: ";
    std::cin.ignore();
    std::cin.getline(prinyato, MaxStrochechka);
    bigBukvi(prinyato);
    std::cout << "Answer for Task 2: " << prinyato << std::endl;

    std::cout << "_____________________________________________________________________________" << std::endl;

    std::cout << "Task 3:" << std::endl;
    int kt;
    std::cout << "Enter k: ";
    std::cin >> kt;
    cubiki(kt);

    delete[] arr;

    return 0;
}
