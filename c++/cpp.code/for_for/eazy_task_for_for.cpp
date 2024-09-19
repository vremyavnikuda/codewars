#include <iostream>

int task_1()
{
    for (int i = 1; i <= 3; ++i)
    {
        for (int j = -1; j >= -3; --j)
        {
            std::cout << i << " " << j << std::endl;
        }
    }
    return 0;
    std::cout << "task_1 done " << std::endl;
}

int task_2()
{
    for (int i = 3; i <= 4; i++)
    {
        for (int j = 1; j <= 3; ++j)
        {
            std::cout << i * j << " ";
        }
        std::cout << std::endl;
    }
    return 0;
    std::cout << "task_2 done" << std::endl;
}

int main()
{
    std::cout << "main task run" << std::endl;
    for (int i = 0; i < 60; ++i)
    {
        for (int j = 0; j < 60; ++j)
        {
            std::cout << "прошло минут: " << i << std::endl;
            std::cout << "прошло секунд: " << j << std::endl;
        }
    }
    std::cout << task_1() << std::endl;
    std::cout << "----------------" << std::endl;
    std::cout << task_2() << std::endl;
}
