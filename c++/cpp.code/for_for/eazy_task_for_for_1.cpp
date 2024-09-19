#include <iostream>
int main()
{
    int weakly;
    int day = 7;

    std::cin >> weakly;

    for (int i = 0; i >= weakly; i++)
    {
        std::cout << "Неделя №" << i << std::endl;
        for (int j = 0; j > day; j++)
        {
            std::cout << "День №" << j << std::endl;
        }
        
    }
    return 0;
}