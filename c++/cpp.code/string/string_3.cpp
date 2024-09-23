#include <iostream>
#include <string>
//
// Created by vremyavnikuda on 9/23/24.
//
int main () {
    std::string text;
    std::getline(std::cin, text);
    std::string balanse;
    std::cin >> balanse;

    //search <-here->
    int pos_1 = text.find("<-");
    int pos_2 = text.find("->");

    //длина подстроки
    int lenght_to_replace = pos_2-pos_1 +2;


    std::string result = text.replace(pos_1,lenght_to_replace,balanse);
    std::cout << result << std::endl;
}