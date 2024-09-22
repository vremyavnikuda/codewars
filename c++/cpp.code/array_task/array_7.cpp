#include <iostream>
//
// Created by vremyavnikuda on 9/22/24.
//
int main() {
    const int SIZE = 13;
    int arr[SIZE];
    int uniqueCount = 0;
    for (int i = 0; i < SIZE; i++) {
        std::cin >> arr[i];
    }
    for (int i = 0; i < SIZE; i++) {
        bool isUnique = true;
        for (int j = 0; j < SIZE; j++) {
            if (i != j && arr[i] == arr[j]) {
                isUnique = false;
                break;
            }
        }
        if (isUnique) {
            uniqueCount++;
        }
    }
    std::cout << "Уникальных чисел найдено " << uniqueCount << std::endl;
    return 0;
}
