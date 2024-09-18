#include <iostream>
int main()
{
    for (int i = 1; i <= 13; i++)
    {
        std::cout << i << std::endl;
        if (i % 5 == 0)
        {
            std::cout << "Бип!!" << std::endl;
        }
    }
}