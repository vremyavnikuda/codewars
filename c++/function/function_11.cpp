//
// Created by vremyavnikuda on 9/25/24.
//

#include <complex>
#include <iostream>

bool is_prime(unsigned int number) {
    if (number<=1)return false;
    for (int i = 2; i <= sqrt(number); ++i)
        if (number % i == 0)
            return false;
    return true;
}

int main() {
    int num;
    std::cin >> num;
    if (is_prime(num)) {
        std::cout << "ДА" << std::endl;
    } else {
        std::cout << "НЕТ" << std::endl;
    }
}
