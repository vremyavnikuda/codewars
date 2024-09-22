//
// Created by vremyavnikuda on 9/22/24.
//

#include <iostream>

int main() {
    const int SIZE = 13;
    int arr[SIZE];
    int count = 0;
    for (int i = 0; i < SIZE; i++) {
        std::cin >> arr[i];
    }
    for (int i = 0; i < SIZE; i++) {
        for(int j = 0; j < SIZE; j++) {
            if(arr[i] == arr[j]) {
                count++;
            }
        }
    }
}
