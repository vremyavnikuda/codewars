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

    ifstream file(path, ios::ate | ios::in);

    if (file.is_open()) {
        streampos end_pos = file.tellg();

        file.seekg(0, ios::beg);

        size_t size = end_pos;
        char *buffer = new char[size + 1];

        file.read(buffer, size);
        buffer[size] = '\0';

        cout << buffer << endl;

        delete[] buffer;
        file.close();
    } else {
        cerr << "Ошибка: не удалось открыть файл." << endl;
    }

    return 0;
}
