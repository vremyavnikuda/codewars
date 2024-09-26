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
        for (int i = 0; i < 3; i++) {
            getline(text, line);
            cout << line << endl;
        }
        text.close();
    } else {
        cerr << "error" << endl;
    }
}
