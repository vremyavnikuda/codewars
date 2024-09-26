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
        int num_1 = 0, num_2 = 0;
        bool found_first = false;

        while (text >> line) {
            int num = stoi(line);

            if (!found_first) {
                num_1 = num;
                found_first = true;
            } else {
                num_2 = num;
                break;
            }
        }
        text.close();
        if (found_first) {
            cout << (found_first && (num_2 != 0) ? (num_1 > num_2 ? num_1 : num_2) : num_1) <<
                    endl;
        }
    }
    return 0;
}
