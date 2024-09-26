#include <iostream>
//
// Created by vremyavnikuda on 9/26/24.
//
int sum_digits(int number) {
    if (number == 0) {
        return 0;
    }
    return (number % 10) + sum_digits(number / 10);
}

int main() {
    int number;
    std::cin >> number;
    std::cout << sum_digits(number);
}