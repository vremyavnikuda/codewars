#include <iostream>
int main()
{
    int x, y;
    std::cin >> x >> y;

    for (int i = 0; i < y; i++)
    {

        for (int j = 1; j < x; j++)
        {
            std::cout << "*";
        }
        std::cout << "*" << std::endl;
    }
}