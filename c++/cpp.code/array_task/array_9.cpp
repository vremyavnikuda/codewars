#include <iostream>
//
// Created by vremyavnikuda on 9/22/24.
//
int main() {
    const int SIZE = 10;
    int arr[SIZE];
    for (int i = 0; i < SIZE; i++) {
        std::cin>>arr[i];
    }

    for(int i=0;i<SIZE-1;i++) {
        for (int j=0;j<SIZE-i-1;j++) {
            if (arr[j]>arr[j+1]) {
                int temp=arr[j];
                arr[j]=arr[j+1];
                arr[j+1]=temp;
            }
        }
    }
    for (int i = 0; i < SIZE; i++) {
        std::cout<<arr[i]<<" ";
    }
}
