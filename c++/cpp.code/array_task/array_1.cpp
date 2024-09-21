#include <iostream>
//
// Created by vremyavnikuda on 9/21/24.
//
int main() {
    int mount_arr[12]= {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    int mount;
    std::cin >> mount;
    std::cout<<mount_arr[mount-1]<<std::endl;
    for (int i=0; i<12;i++) {
        std::cout<<mount_arr[i]<<" ";
    }
}