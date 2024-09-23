#include <iostream>
//
// Created by vremyavnikuda on 9/23/24.
//
int main() {
    int lenght;
    std::cin >> lenght;

    char str[lenght];
    std::cin >> str;

    bool flag=true;

    for (int i = 0; i < lenght / 2; i++) {
        if (str[i] != str[lenght - i - 1]) {
            flag = false;
            break;
        }
    }
    if (flag) {
        std::cout << "Да" << std::endl;
    }else
        std::cout << "Нет" << std::endl;
}
