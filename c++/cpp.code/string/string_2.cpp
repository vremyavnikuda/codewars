#include <iostream>
//
// Created by vremyavnikuda on 9/23/24.
//
int main() {
    std::string name;
    std::cin >> name;

    std::string love = "I love you, ";
    std::string result = name.insert(0, love);
    std::cout << result << "!" << std::endl;
}
