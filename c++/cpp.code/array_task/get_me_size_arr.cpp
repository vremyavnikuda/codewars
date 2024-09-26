#include <iostream>
#include <ostream>
//
// Created by vremyavnikuda on 9/27/24.
//
int main() {
    int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    int size = sizeof(arr) / sizeof(arr[0]);
    std::cout << size << std::endl;

    for (auto n: arr) {
        std::cout << n << " ";
    }
    std::cout << std::endl;

    auto arr_func = []() {
        const int row = 3, col = 2;
        int arr[row][col]{{1, 2}, {3, 4}, {5, 6}};

        for (auto &sub_number: arr) {
            for (int number: sub_number) {
                std::cout << number << " ";
            }
            std::cout << std::endl;
        }
    };
    arr_func();
}
