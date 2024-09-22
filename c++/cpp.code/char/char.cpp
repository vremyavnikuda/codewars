#include <iostream>
//
// Created by vremyavnikuda on 9/23/24.
//
int main() {
    char *string = "Hello";
    for (int a = 0;; a++) {
        char symbol = string[a];
        if (symbol == 0) {
            break;
        }
        std::cout << symbol;
    }
}
