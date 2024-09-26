#include <fstream>
#include <iostream>
//
// Created by vremyavnikuda on 9/26/24.
//
int main() {
    std::ifstream textFile("/home/vremyavnikuda/repository/codewars/c++/cpp.code/files/sample_code.txt", std::ios::ate);

    int size = textFile.tellg();

    std::cout << size << std::endl;
}
