//
// Created by vremyavnikuda on 02.09.24.
//
#include <string>
#include <vector>
#include <iostream>

std::vector<std::string> solution(const std::string &s)
{
    std::vector<std::string> result;
    std::string str = s;
    if (str.length() % 2 != 0) // Исправлено условие
    {
        str += "_";
    }
    for (size_t i = 0; i < str.length(); i += 2) // Увеличиваем i на 2
    {
        result.push_back(str.substr(i, 2));
    }
    // Выводим результат
    for (const auto &pair : result)
    {
        std::cout << pair << " ";
    }
    std::cout << std::endl;
    return result;
}

int main()
{
    std::vector<std::string> result = solution("abcdabcdabcdabcdabcdabcdabcdabcd");

    // Если вы хотите использовать результат:
    std::cout << "Количество пар: " << result.size() << std::endl;

    return 0;
}