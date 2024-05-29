#include <iostream>
#include <string>

std::string generator2006()
{
    std::string gen;
    for (int i = 10; i < 100; i++)
    {
        std::string origa = std::to_string(i);

        std::string reverse = std::string(origa.rbegin(), origa.rend());

        gen += origa + reverse;
    }
    std::cout << gen << std::endl;
    return gen;
}
char get_k(int k)
{
    std::string gen = generator2006();
    return gen[k - 1];
}

int main()
{
    int k;
    std::cout << "Enter k: ";
    std::cin >> k;

    char result = get_k(k);

    std::cout << "Answer: " << result;
}


