#include <iostream>
int main()
{
    int a, b;
    std::cin >> a >> b;
    int result = 0;
    for (int i = a; i <= b; i++)
    {
        result += a;
        a++;
    }
    std::cout << result << std::endl;
}
