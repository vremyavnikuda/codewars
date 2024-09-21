#include <iostream>
int main()
{
    int weakly;
    int day = 7;

    std::cin >> weakly;

    for (int i = 1; i <= weakly; ++i)
    {
        std::cout << "Неделя №" << i << std::endl;
        for (int j = 1; j <= day; ++j)
        {
            std::cout << "День №" << j << std::endl;
        }
    }
}