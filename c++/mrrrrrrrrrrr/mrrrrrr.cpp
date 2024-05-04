#include <iostream>
#include <algorithm>
using namespace std;

// Функция для решения задачи с использованием условного оператора if
void sortByIf()
{
    int a, b, c;
    cout << "Enter numbers" << endl; // ввод данных
    cin >> a >> b >> c;

    // сортировка условным оператором и командой swap
    if (a < b)
    {
        swap(a, b);
    }
    if (b < c)
    {
        swap(b, c);
    }
    if (a < b)
    {
        swap(a, b);
    }

    cout << "Sorted numbers: " << a << ", " << b << ", " << c << endl; // вывод результата
}

// Функция для решения задачи с использованием условного оператора ?:
void sortByTernaryOperator()
{
    int num1, num2, num3;

    cout << "Enter three numbers: ";
    cin >> num1 >> num2 >> num3;

    (num1 > num2 ? (num1 > num3 ? (num2 > num3 ? 0 : (swap(num2, num3), 0)) : (swap(num1, num3), swap(num2, num3), 0)) : (num2 > num3 ? (swap(num1, num2), 0) : (num2 > num1 ? (static_cast<void>(swap(num1, num2)), swap(num1, num3), 0) : (swap(num1, num3), 0))));

    cout << "Answer: " << num1 << " " << num2 << " " << num3 << endl;
}

int main()
{
    // Вызываем нужную функцию для сортировки
    // sortByIf(); // Решение с использованием условного оператора if
    sortByTernaryOperator(); // Решение с использованием условного оператора ?:

    return 0;
}
