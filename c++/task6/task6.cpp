/*
    Задание 6
    Напечатать в обратном порядке заданный текст (в конце текста - точка)
    с использованием рекурсии.
*/

#include <iostream>

// Рекурсивная функция для печати текста в обратном порядке
void Revers() {
    char symbol;
    std::cin.get(symbol); // Получаем символ
    
    if (symbol != '.') {
        // Если символ не точка, продолжаем рекурсивно вызывать функцию
        Revers();
        // Печатаем символ после выхода из рекурсии (обратный порядок)
        std::cout << symbol;
    }
}

int main() {
    std::cout << "Введите текст, за которым следует точка:" << std::endl;
    
    // Вызываем функцию printReverse() для печати текста в обратном порядке
    Revers();
    
    std::cout << std::endl; // Переводим строку, чтобы результат выглядел читаемо
    
    return 0;
}