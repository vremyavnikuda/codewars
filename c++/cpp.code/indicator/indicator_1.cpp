#include <iostream>
//
// Created by vremyavnikuda on 9/25/24.
//
int main() {
    std::string  x = "hello world";
    std::string *y = &x;
    std::cout << *y << std::endl;
}
