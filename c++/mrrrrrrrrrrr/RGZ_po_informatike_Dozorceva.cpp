#include <iostream>
#include <vector>
#include <sstream>
#include <locale>
#include <codecvt>

bool hasRepeatedFirstChar(const std::wstring &word)
{
    if (word.empty())
    {
        return false;
    }
    wchar_t firstChar = word[0];
    for (size_t i = 1; i < word.size(); ++i)
    {
        if (word[i] == firstChar)
        {
            return true;
        }
    }
    return false;
}

std::vector<std::wstring> split(const std::wstring &str)
{
    std::vector<std::wstring> result;
    std::wstring word;
    for (wchar_t ch : str)
    {
        if (std::iswalnum(ch))
        {
            word += ch;
        }
        else
        {
            if (!word.empty())
            {
                result.push_back(word);
                word.clear();
            }
        }
    }
    if (!word.empty())
    {
        result.push_back(word);
    }
    return result;
}

std::wstring filterWords(const std::wstring &input)
{
    std::vector<std::wstring> words = split(input);
    std::vector<std::wstring> result;
    for (const std::wstring &word : words)
    {
        if (hasRepeatedFirstChar(word))
        {
            result.push_back(word);
        }
    }

    std::wostringstream oss;
    for (size_t i = 0; i < result.size(); ++i)
    {
        if (i != 0)
        {
            oss << L" ";
        }
        oss << result[i];
    }
    return oss.str();
}

int main()
{
    std::locale::global(std::locale("en_US.UTF-8"));
    std::wcin.imbue(std::locale());
    std::wcout.imbue(std::locale());

    std::wstring input1 = L"Группа___мультимедийных_____средств…обучения";
    std::wstring input2 = L"drink dor double end else need key reader red year";

    std::wstring output1 = filterWords(input1);
    std::wstring output2 = filterWords(input2);

    std::wcout << L"Input: " << input1 << std::endl;
    std::wcout << L"Output: " << output1 << std::endl;

    std::wcout << L"Input: " << input2 << std::endl;
    std::wcout << L"Output: " << output2 << std::endl;

    return 0;
}
