#include <iostream>
//
// Created by vremyavnikuda on 9/22/24.
//
int main() {
    int arr[7];
    for (int i = 0; i < 7; ++i) {
        std::cin >> arr[i];
    }

    for (int i = 6; i >= 0; i--) {
        std::cout << arr[i] << " ";
    }
    delete[]arr;
}
