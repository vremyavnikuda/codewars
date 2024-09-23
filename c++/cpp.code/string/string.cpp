//
// Created by vremyavnikuda on 9/23/24.
//

#include <iostream>
#include <string>

int main() {
    std::string name ;

    getline(std::cin,name);

    std::cout<<"Привет, "<<name<<"!"<<std::endl;
    std::cout<<name.length()<<std::endl;
    int pos = name.find("Andrew");
    std::cout<<pos<<std::endl;
}
