//
// Created by vremyavnikuda on 9/24/24.
//

#include <iostream>

float to_celsius(float fahrenheit) {
    float celsius = (fahrenheit - 32) * 5 / 9;
    return celsius;
}
int main() {
    float fan ;
    std::cin>>fan;
    std::cout<<to_celsius(fan);
}