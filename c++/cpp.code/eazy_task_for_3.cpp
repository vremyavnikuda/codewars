#include <iostream>
int main()
{
    int max = 0;
    for (int i = 16; i > 0; --i)
    {
        int run;
        std::cin >> run;
        if (run > max)
        {
            max = run;
        }
    }
    std::cout << max << std::endl;
}