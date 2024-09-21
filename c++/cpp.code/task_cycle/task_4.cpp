#include <iostream>
#include <complex>
int main()
{
    int a, b;
    std::cin >> a >> b;

    for (int i = 1; i <= b; ++i)
    {
        int result = std::pow(a, i);
        std::cout << a << " в " << i << "-й степени равно " << result << std::endl;
    }
}