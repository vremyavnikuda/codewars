#include <iostream>
//
// Created by vremyavnikuda on 9/23/24.
//
int main() {
    char strings[5][100]={{"Пончики - это просто бублики с посыпкой"},{"Клубничный монстр"},{"Тарталетки с брусникой"},{"КРЕВЕТКИ ЗАХВАТЯТ МИР!"},{"Крабонатор"}};

    for (char (&str)[100]:strings) {
        std::cout<<str<<std::endl;
    }
}