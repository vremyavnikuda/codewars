/*
Определить функцию, которая оставляет в строке слова,  встречающиеся в последовательности только один раз (использовать функции strcmp(); strcpy();)

Ввод (исходная строка)
…the GDPR began requiring companies to: provide data breach notifications; appoint a data-protection officer; require user consent for data processing; anonymize data for privacy…

Вывод (строка-результат)
the GDPR began requiring companies to provide breach notifications appoint a protection officer require user consent for processing anonymize for privacy

Ввод (исходная строка)
("проверка равенства суммы первых двух цифр четырехзначного числа сумме двух его последних цифр.");
Вывод (строка-результат)
проверка равенства суммы первых четырехзначного числа сумме его последних

Ввод (исходная строка)
int main(){ fgets(text, sizeof(text), stdin);text[strcspn(text, "\n")] = '\0';return 0;}
Вывод (строка-результат)
int main fgets sizeof stdin strcspn n return
*/

#include <iostream>
#include <cstring>
#include <cctype>

// Функция для замены знаков препинания на пробелы
void replacePunctuationWithSpaces(char *str)
{
    for (int i = 0; str[i]; ++i)
    {
        if (ispunct(static_cast<unsigned char>(str[i])))
        {
            str[i] = ' ';
        }
    }
}

// Функция для нахождения уникальных слов
void findUniqueWords(char *input, char result[][50], int &uniqueCount)
{
    // Массив для хранения всех слов
    char words[100][50];
    int wordCount = 0;
    // Разделяем строку на слова
    char *token = strtok(input, " ");
    while (token != nullptr)
    {
        strcpy(words[wordCount++], token);
        token = strtok(nullptr, " ");
    }
    // Ищем уникальные слова
    for (int i = 0; i < wordCount; ++i)
    {
        bool isUnique = true;
        for (int j = 0; j < wordCount; ++j)
        {
            if (i != j && strcmp(words[i], words[j]) == 0)
            {
                isUnique = false;
                break;
            }
        }
        if (isUnique)
        {
            strcpy(result[uniqueCount++], words[i]);
        }
    }
}

int main()
{
    char input[1000];
    std::cout << "Enter the input string: ";
    std::cin.getline(input, 1000);
    // Заменяем знаки препинания пробелами
    replacePunctuationWithSpaces(input);
    // Массив для хранения уникальных слов
    char uniqueWords[100][50];
    int uniqueCount = 0;
    // Находим уникальные слова
    findUniqueWords(input, uniqueWords, uniqueCount);

    std::cout << "Resulting string: ";
    for (int i = 0; i < uniqueCount; ++i)
    {
        if (i > 0)
        {
            std::cout << " ";
        }
        std::cout << uniqueWords[i];
    }
    std::cout << std::endl;
    return 0;
}
