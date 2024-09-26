#include <iostream>
//
// Created by vremyavnikuda on 9/26/24.
//
//fib recursion
int fib(int number) {
    if (number == 1) {
        return 0;
    } else if (number == 2) {
        return 1;
    }
    return fib(number - 1) + fib(number - 2);
}

int main() {
    int number;
    std::cin >> number;
    std::cout << fib(number);
}
