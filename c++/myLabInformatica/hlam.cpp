#include <iostream>
#include <string>

int CountPos(const std::string &str)
{
    int cnt = 0;
    for (int i = 0; str[i] != '\0'; i++)
    {
        cnt++;
    }
    return cnt;
}

std::string generator2004()
{
    std::string chislo;
    for (int number = 10; number < 100; ++number)
    {

        std::string origa = std::to_string(number);

        std::string reversed = std::string(origa.rbegin(), origa.rend());

        chislo += origa + reversed;
    }
    std::cout << "Proverka generatora 2004: " << chislo << std::endl;
    return chislo;
}

// к-тая циферкаа в последовательности

char otvetik(const std::string &sgenereno, int k)
{
    return sgenereno[k - 1];
}

int main()
{

    std::string sequence = generator2004();

    // Подсчитываем количество цифр в последовательности
    int vsego_ciferok = CountPos(sequence);

    int k;
    std::cout << "Enter k (1 < k < 360: ";
    std::cin >> k;

    if (k < 1 || k > vsego_ciferok)
    {
        std::cerr << "Dolbaeb? 1 < k < 360" << std::endl;
        return 1;
    }

    // Получаем k-ю цифру
    char result = otvetik(sequence, k);

    std::cout << "Otvetik: " << result << std::endl;
    std::cout << "CountPos zaebos: " << vsego_ciferok << std::endl;

    return 0;
}
