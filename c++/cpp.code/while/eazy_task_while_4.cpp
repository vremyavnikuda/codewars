#include <iostream>
int main()
{
    int number;
    int revers_number = 0;
    std::cin >> number;

    while (number > 0)
    {
        revers_number = revers_number * 10 + number % 10;
        number = number / 10;
    }
    std::cout << revers_number << std::endl;
}