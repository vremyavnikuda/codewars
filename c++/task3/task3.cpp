#include <stdlib.h>
#include <string>
#include <iostream>

/*Задание 3 
Описать рекурсивную логическую функцию simm (s,i,j), проверяющую, является ли симметричной 
часть строки s, начинающаяся i-м и заканчивающаяся j-м еѐ элементами.
 */
int Simmetr(const std::string& s, int l, int r) {
 if (l >= r)
        return 0;
    if (s[l] != s[r])
        return 1;
    return Simmetr(s, l + 1, r - 1);
}

int main() {
 system("chcp 1251");

    std::string s;
    std::cout << "Введите строку для проверки на симметрию: ";
    std::cin >> s;
    
    int l = 0; // Начальный индекс
    int r = s.length() - 1; // Конечный индекс

    if (Simmetr(s, l, r)) {
        std::cout << "Строка симметрична\n";
    } else {
        std::cout << "Строка не симметрична\n";
    }

    return 0;
}
