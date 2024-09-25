//
// Created by vremyavnikuda on 9/24/24.
//

#include <iostream>

bool is_leap_year(int year);
int days(int month, int year);

bool is_valid_date(int day, int month, int year) {
    if (month < 1 || month > 12) {
        return false;
    }
    int func_data = days(month, year);
    return (day >= 1 && day <= func_data);
}

bool is_leap_year(int year) {
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

int days(int month, int year) {
    if (is_leap_year(year)) {
        switch (month) {
        case 1:
            return 31;
        case 2:
            return 29;
        case 3:
            return 31;
        case 4:
            return 30;
        case 5:
            return 31;
        case 6:
            return 30;
        case 7:
            return 31;
        case 8:
            return 31;
        case 9:
            return 30;
        case 10:
            return 31;
        case 11:
            return 30;
        case 12:
            return 31;
        default:
            return 0;
        }
    } else if (year) {
        switch (month) {
        case 1:
            return 31;
        case 2:
            return 28;
        case 3:
            return 31;
        case 4:
            return 30;
        case 5:
            return 31;
        case 6:
            return 30;
        case 7:
            return 31;
        case 8:
            return 31;
        case 9:
            return 30;
        case 10:
            return 31;
        case 11:
            return 30;
        case 12:
            return 31;
        default:
            return 0;
        }
    }
}

int main() {
    int d, m, y;
    std::cin >> d >> m >> y;
    if (is_valid_date(d, m, y)) {
        std::cout << "ДА";
    } else {
        std::cout << "НЕТ";
    }
}
