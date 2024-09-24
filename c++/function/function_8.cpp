//
// Created by vremyavnikuda on 9/24/24.
//

#include <iostream>

bool _is_leap_year(int year) {
    bool flag = false;
    if (year % 4 == 0 && year % 100 != 0 || year % 400 == 0) {
        flag = true;
    } else {
        flag = false;
    }
    return flag;
}

int main() {
    int year;
    std::cin >> year;

    if (_is_leap_year(year)) {
        std::cout << "ДА";
    } else {
        std::cout << "НЕТ";
    }
}
