#include <iostream>
int main()
{
    int factorial;
    std::cin >> factorial;
    int result = 1;
    for (int i = 1; i <= factorial; i++)
    {
        result = result * i;
    }
    std::cout << result << std::endl;
}