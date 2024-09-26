//
// Created by vremyavnikuda on 9/26/24.
//

#include <fstream>
#include <iostream>

int main() {
    std::ifstream input("hello-world.txt");
    std::string line;

    std::getline(input, line);

    std::cout<<line<<std::endl;
}
