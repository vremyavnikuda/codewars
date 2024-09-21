#include <iostream>
//
// Created by vremyavnikuda on 9/22/24.
//
int main() {
    int squares[30];

    for (int i = 0; i < 30; ++i) {
        squares[i] = i * i;
    }
    for(int i=0;i<30;++i) {
        std::cout<<squares[i]<<" ";
    }
    delete[]squares;
}
