#include <iostream>
#include <sstream>
#include <vector>

// Функция для преобразования слова к заданной длине
std::string transformWord(const std::string &word, size_t length)
{
    if (word.length() > length)
    {
        return word.substr(0, length); // Обрезаем слово
    }
    else if (word.length() < length)
    {
        // Дополняем слово последней буквой
        return word + std::string(length - word.length(), word.back()); 
    }
    // Если длина слова уже равна заданной, возвращаем его без изменений
    return word; 
}
// Функция для преобразования строки
std::string transformString(const std::string &input, size_t length)
{
    std::istringstream iss(input);
    std::ostringstream oss;
    std::string word;
    bool firstWord = true;

    while (iss >> word)
    {
        if (!firstWord)
        {
            // Добавляем пробел перед каждым словом, кроме первого
            oss << " "; 
        }
        oss << transformWord(word, length);
        firstWord = false;
    }
    return oss.str();
}
int main()
{
    std::string input;
    size_t length;
    std::cout << "Enter the input string: ";
    std::getline(std::cin, input);
    std::cout << "Enter the desired word length: ";
    std::cin >> length;
    std::string output = transformString(input, length);
    std::cout << "Transformed string: " << output << std::endl;
    return 0;
}
