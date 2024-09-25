#include <iostream>
//
// Created by vremyavnikuda on 9/25/24.
//
int get_max(int arr[], int size) {
    int max = arr[0];
    for (int i = 1; i < size; i++) {
        if (arr[i] > max) {
            max = arr[i];
        }
    }
    return max;
}

int get_max_rec(int arr[], int size) {
    if (size == 1) {
        return arr[0];
    }

    int a = arr[0];
    int b = get_max_rec(arr + 1, size - 1);

    return a > b ? a : b;
}

int main() {
    int size;
    std::cin >> size;
    int arr[size];
    for (int i = 0; i < size; i++) {
        std::cin >> arr[i];
    }
    std::cout << get_max(arr, size) << std::endl;
    std::cout << get_max_rec(arr, size) << std::endl;
}
