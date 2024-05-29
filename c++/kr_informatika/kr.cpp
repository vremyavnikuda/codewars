#include <iostream>
#include <fstream>
#include <string>
/*
Контрольная работа
Вариант 7
Дан текстовый файл Ф1. Скопировать в файл Ф2 строки с нечётными номерами, а в файл Ф3 строки с чётными номерами.
*/
// Функция для копирования строк с нечетными номерами из одного файла в другой
void copyOddLines(std::ifstream &source, std::ofstream &destination)
{
    std::string line;
    // Начинаем считать строки с нуля
    int lineNumber = 0;

    // Читаем строки из исходного файла
    while (std::getline(source, line))
    {
        // Если номер строки нечетный, копируем ее в целевой файл
        if (lineNumber % 2 != 0)
        {
            destination << line << std::endl;
        }
        lineNumber++;
    }
}

// Функция для копирования строк с четными номерами из одного файла в другой
void copyEvenLines(std::ifstream &source, std::ofstream &destination)
{
    std::string line;
    // Начинаем считать строки с нуля
    int lineNumber = 0;

    // Читаем строки из исходного файла
    while (std::getline(source, line))
    {
        // Если номер строки четный, копируем ее в целевой файл
        if (lineNumber % 2 == 0)
        {
            destination << line << std::endl;
        }
        lineNumber++;
    }
}

int main()
{
    std::ifstream file1("F1.txt");
    if (!file1.is_open())
    {
        std::cerr << "Unable to open file F1.txt\n";
        return 1;
    }
    std::ofstream file2("F2.txt");
    if (!file2.is_open())
    {
        std::cerr << "Unable to open file F2.txt\n";
        return 1;
    }
    std::ofstream file3("F3.txt");
    if (!file3.is_open())
    {
        std::cerr << "Unable to open file F3.txt\n";
        return 1;
    }
    // Копируем строки с нечетными номерами из Ф1 в Ф2
    copyOddLines(file1, file2);
    // Возвращаем указатель на начало файла Ф1
    file1.clear();
    file1.seekg(0, std::ios::beg);
    // Копируем строки с четными номерами из Ф1 в Ф3
    copyEvenLines(file1, file3);
    // Закрываем все файлы
    file1.close();
    file2.close();
    file3.close();
    std::cout << "Lines copied successfully to files F2.txt and F3.txt\n";
    return 0;
}
