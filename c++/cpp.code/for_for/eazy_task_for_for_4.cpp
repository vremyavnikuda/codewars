#include <iostream>

int main()
{
    int x;
    std::cin >> x;

    // Печатаем первую половину (увеличиваем количество звездочек)
    for (int c = 0; c < x / 2 + 1; c++)
    {
        for (int j = 0; j <= c; j++)
        {
            std::cout << "*";
        }
        std::cout << std::endl;
    }

    // Печатаем вторую половину (уменьшаем количество звездочек)
    for (int c = x / 2 - 1; c >= 0; c--)
    {
        for (int j = 0; j <= c; j++)
        {
            std::cout << "*";
        }
        std::cout << std::endl;
    }

    return 0;
}
