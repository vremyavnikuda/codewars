#include <iostream>
int main()
{
    float sum;
    float mass;

    do
    {
        std::cin >> mass;
        sum += mass;
    } while (mass != 0);
    std::cout << sum << std::endl;
}