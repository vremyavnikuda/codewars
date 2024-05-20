/*
1)  Словом считать любую последовательность, содержащую только русские и латинские буквы. Разделители между словами и их количество может быть любым.
 9: В каждом слове строки все последующие вхождения первого символа этого слова написать заглавной буквой.
 
 2)  Создать строку (длина  равна k), которая представляет собой заданную последовательность.
 9:     Последовательность 182764125216343…, в которой выписаны подряд кубы всех натуральных чисел.
 
 */
#include <iostream>
#include <string>
#include <cctype>
#include <cmath>
//функция для первого задания: поменять все последующие взождения первого символа на заглавные



void Task_1_BigBukvi(char*strochka)
{
    if (strochka == nullptr || *strochka == '\0')
        return;

    char FirstBukva = *strochka;
    bool FirstProideno = false; // флаг для определения что первый символ пройден

    for (size_t i = 0; strochka[i] != '\0'; i++)
    { // цикл для прохлождения по всему слову до последней буквы
        if (tolower(strochka[i] == tolower(FirstBukva)))
        { // замена строчной на заглавную
            if (FirstProideno)
            {
                strochka[i] = toupper(strochka[i]);
            }
            else
            { // если предыдущее условие не выполняется, значит первый символ не пройден -> меняем флаг
                FirstProideno = true;
            }
        }
    }
}

void Task_2_Cubiki(int chislo)
{
    // int chislo;

    for (int i = 1; i <= chislo; i++)
    {
        long cube = std::pow(i, 3); // возведение в третью степерь
        std::cout << cube;          // вывод
    }
    std::cout << std::endl;
}

int main()
{
    // Первое задание
    std::cout << std::endl;
    std::cout << "Task 1:" << std::endl;

    const int MaxStrochechka = 100; // максимальный размер строки
    char prinyato[MaxStrochechka];

    std::cout << "Enter the line: "; // ввод пользователем
    std::cin.getline(prinyato, MaxStrochechka);

    Task_1_BigBukvi(prinyato);                                   // прогон строки через функцию
    std::cout << "Answer for Task 1: " << prinyato << std::endl; // вывод 1 задания

    std::cout << "_____________________________________________________________________________" << std::endl;

    // Второе задание
    std::cout << std::endl;
    std::cout << "Task 2:" << std::endl;

    char k_char;

    std::cout << "Enter k: "; // ввод к
    std::cin >> k_char;

    int k = k_char - '0';

    std::cout << "Answer for Task 2: " << std::endl;
    Task_2_Cubiki(k);

    return 0;
}
