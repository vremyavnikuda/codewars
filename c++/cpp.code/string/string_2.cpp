#include <iostream>
//
// Created by vremyavnikuda on 9/23/24.
//
int main() {
    std::string name;
    std::cin >>name;
    std::string love;
    love.insert(0, "I love you, ").append(name).append("!");
}
