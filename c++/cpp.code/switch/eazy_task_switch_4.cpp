#include <iostream>
//
// Created by vremyavnikuda on 9/23/24.
//
int getRealFloor(int f) {
    return f<=0?f:f<13?f-1:f-2;
}

int main() {
    int result = getRealFloor(13);
    std::cout << result << std::endl;
}
