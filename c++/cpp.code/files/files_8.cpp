#include <fstream>
#include <iostream>
#include <string>
//
// Created by vremyavnikuda on 9/26/24.
//
using namespace std;

int main() {
    string path;
    cin >> path;

    ifstream text(path);

    if (text.is_open()) {
        string line;
        while(text >>line) {
            cout << line<<" ";
        }
    }else {
        cout << "Файл не существует" << endl;
    }
}
