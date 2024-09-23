#include <algorithm>
#include <iostream>
#include <ostream>
//
// Created by vremyavnikuda on 9/24/24.
//
unsigned short int expressionsMatter(unsigned short int a, unsigned short int b, unsigned short int c) {
    int result_1 = (a + b + c);
    int result_2 = (a * b * c);
    int result_3 = ((a + b) * c);
    int result_4 = (a * (b + c));
    int result_5 = (a * (b * c));
    int result_6 = (a + (b * c));

    return std::max({result_1,result_2,result_3,result_4,result_5,result_6});
}

int main() {
    std::cout<<expressionsMatter(5,6,1)<<std::endl;
}
