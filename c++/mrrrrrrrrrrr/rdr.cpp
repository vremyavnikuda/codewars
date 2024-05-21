#include <iostream>
#include <vector>
#include <iomanip>

// Функция для создания таблицы сложения
std::vector<std::vector<int>> createAdditionTable(int base)
{
    std::vector<std::vector<int>> table(base, std::vector<int>(base));
    for (int i = 0; i < base; ++i)
    {
        for (int j = 0; j < base; ++j)
        {
            table[i][j] = (i + j) % base;
        }
    }
    return table;
}

// Функция для создания таблицы умножения
std::vector<std::vector<int>> createMultiplicationTable(int base)
{
    std::vector<std::vector<int>> table(base, std::vector<int>(base));
    for (int i = 0; i < base; ++i)
    {
        for (int j = 0; j < base; ++j)
        {
            table[i][j] = (i * j) % base;
        }
    }
    return table;
}

// Функция для вывода таблицы
void printTable(const std::vector<std::vector<int>> &table, const std::string &title)
{
    std::cout << title << ":\n";
    for (const auto &row : table)
    {
        for (int value : row)
        {
            std::cout << std::setw(2) << value << " ";
        }
        std::cout << "\n";
    }
    std::cout << "\n";
}

// Функция для умножения с выводом промежуточных результатов
void multiplyWithIntermediateResults(int a, int b, int base)
{
    int result = 0;
    int place = 1;
    std::vector<int> intermediateResults;

    std::cout << "Multiplying " << a << " and " << b << " in base " << base << ":\n";

    while (b > 0)
    {
        int digit = b % base;
        b /= base;
        int partialResult = (a * digit) % base;
        intermediateResults.push_back(partialResult * place);
        result = (result + partialResult * place) % base;
        place *= base;
    }

    for (size_t i = 0; i < intermediateResults.size(); ++i)
    {
        std::cout << "Intermediate result " << i + 1 << ": " << intermediateResults[i] << "\n";
    }
    std::cout << "Final result: " << result << "\n";
}

// Основная функция для демонстрации
int main()
{
    for (int base = 3; base <= 9; ++base)
    {
        auto addTable = createAdditionTable(base);
        auto multTable = createMultiplicationTable(base);

        std::cout << "Base " << base << " addition table:\n";
        printTable(addTable, "Addition Table");

        std::cout << "Base " << base << " multiplication table:\n";
        printTable(multTable, "Multiplication Table");

        // Пример умножения для демонстрации промежуточных результатов
        multiplyWithIntermediateResults(2, 3, base);
        std::cout << "\n"
                  << std::string(20, '=') << "\n";
    }

    return 0;
}
