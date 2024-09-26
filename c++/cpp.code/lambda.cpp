#include <iostream>
//
// Created by vremyavnikuda on 9/27/24.
//
int main() {
    int number = 1;
    auto lambda = []() {
        std::cout << "Hello world!" << std::endl;
    };
    lambda();

    auto print_number = [number](int x) {
        std::cout << x << std::endl;
    };
    print_number(number);
}
