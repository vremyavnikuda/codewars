#include <iostream>
//
// Created by vremyavnikuda on 9/23/24.
//
int main() {
    int lenght;
    std::cin >> lenght;
    char word[lenght + 1];
    std::cin >> word;

    for (int i = lenght-1; i >= 0; i--) {
        std::cout << word[i];
    }
}
