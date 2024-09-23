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
    int counter = 0;
    for (int i = 0; i < lines.size(); i++) {
        ++counter;
        std::string temp = std::to_string(counter).append(": ").append(lines[i]);
        result.push_back(temp);
    }
    /*for (const auto &line : result) {
        std::cout << line << std::endl;
    }*/
    return result;
}

/*int main() {
    std::vector<std::string> lines = {"a", "b", "c"};
    number(lines);
}*/