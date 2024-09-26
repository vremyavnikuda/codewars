#include <fstream>
#include <iostream>
//
// Created by vremyavnikuda on 9/26/24.
//
int main() {
    std::string path;
    std::cin >> path;
    std::ifstream input(path);
    if (input.is_open()) {
        std::string line;
        for(int i=0;i<3;i++) {
            input>>line;
            std::cout << line << " ";
        }
        input.close();
    }else {
        std::cerr << "fatal error";
    }
}
