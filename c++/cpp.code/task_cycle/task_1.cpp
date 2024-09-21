#include <iostream>
int main()
{
    int count;
    int number;
    int count_positive_number = 0;
    std::cin >> count;
    if (count != 0)
    {
        for (int i = 0; i < count; i++)
        {
            std::cin >> number;
            if (number > 0)
            {
                count_positive_number++;
            }
        }
        std::cout << count_positive_number;
    }
    else
    {
        std::cout << 0 << std::endl;
    }
}