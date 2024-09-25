//
// Created by vremyavnikuda on 9/25/24.
//

#include <iostream>

int factorial(int number) {
    if (number == 1 || number ==0) {
        return number;
    }
    return number * factorial(number - 1);
}

int main() {
    int number;
    std::cin >> number;
    std::cout << factorial(number) << std::endl;
}
