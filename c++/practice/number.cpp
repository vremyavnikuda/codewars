#include <iostream>
#include <ostream>
#include <string>
#include <vector>
//
// Created by vremyavnikuda on 9/24/24.
//https://ravesli.com/urok-91-tsikl-foreach/
//https://www.codewars.com/kata/54bf85e3d5b56c7a05000cf9/solutions/cpp

std::vector<std::string> number(const std::vector<std::string> &lines) {
    std::vector<std::string> result;
    for (int i = 0; i < lines.size(); i++) {
        std::string temp_string = std::to_string(i+1).append(": ").append(lines[i]);
        result.push_back(temp_string);
    }
    for (const auto &line : result) {
        std::cout << line << std::endl;
    }
    return result;
}

int main() {
    std::vector<std::string> lines = {"a", "b", "c"};
    number(lines);
}
