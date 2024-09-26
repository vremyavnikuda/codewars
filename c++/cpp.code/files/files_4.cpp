//
// Created by vremyavnikuda on 9/26/24.
//

#include <fstream>
#include <iostream>
#include <string>
using namespace std;
int main() {
    string path;
    cin >> path;

    ifstream text(path);
    if (text.is_open()) {
        cout << "Файл существует" << endl;
    }else {
        cout<<"Файл не найден"<<endl;
    }
}