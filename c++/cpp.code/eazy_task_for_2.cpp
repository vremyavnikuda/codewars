#include <iostream>
int main()
{
    float result=0;
    for (int i = 15; i > 0; i--)
    {
        float num;
        std::cin >> num;
        result += num;
    }
    std::cout << result << std::endl;
}