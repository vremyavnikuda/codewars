#include <iostream>
int main()
{
    int number;
    int sum = 0;

    std::cin >> number;

    while (number > 0)
    {
        int last_digit = number % 10;
        sum += last_digit;
        number = number / 10;
    }

    std::cout << sum << std::endl;
}
