#include <iostream>
//
// Created by vremyavnikuda on 9/21/24.
//
int main() {
    int size;
    std::cin >> size;
    int arr[size];
    for (int i = 0; i < size; i++) {
        std::cin >> arr[i];
    }

    for(int i=0;i<size;i++) {
        std::cout<<arr[i]<<" ";
    }
}
