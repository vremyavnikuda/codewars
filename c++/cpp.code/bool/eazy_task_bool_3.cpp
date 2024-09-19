#include <iostream>
using namespace std;
int main()
{
    int number;
    cin >> number;

    if (number > 99 && number <= 999)
    {
        cout << "ДА";
    }
    else
    {
        cout << "НЕТ";
    }
}