//
// Created by vremyavnikuda on 9/24/24.
//

#include <iostream>
#include <ostream>
#include <string>
void hello(std::string name) {
    std::cout<<"Привет, "<<name<<"!"<<std::endl;
}
int main() {
    std::string name;
    std::cin >>name;
    hello(name);
}