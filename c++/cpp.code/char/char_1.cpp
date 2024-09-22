#include <iostream>
#include <ostream>
//
// Created by vremyavnikuda on 9/23/24.
//
int main() {
    char hello[] = "Hello World";
    for (int i = 0;; i++) {
        char symbol = hello[i];
        if (symbol == '\0') {
            break;
        }
        std::cout<<symbol;
    }
}
