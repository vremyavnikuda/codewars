#include <list>
#include <string>
#include <iostream>
// Проверка на главную букву
bool mainLetter(const std::string &word)
{
    if (word.empty())
    {
        return false;
    }
    char firstLetter = std::tolower(word.front());
    char lastLetter = std::tolower(word.back());

    return firstLetter == lastLetter;
}

// Количество главных букв
int countFirstLetters(const std::list<std::string> &words)
{
    int count = 0;
    for (const auto &word : words)
    {
        if (mainLetter(word))
        {
            count++;
        }
    }
    return count;
}
int main()
{
    std::list<std::string> words = {
        "level",
        "world",
        "deified",
        "radar",
        "hello"
        };

    int result = countFirstLetters(words);

    std::cout << "Kol-vo letter: " << result << std::endl;
    return 0;
}