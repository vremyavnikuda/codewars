//
// Created by vremyavnikuda on 9/27/24.
//
#include <iostream>
#include <string>
#include <fstream>
using namespace std;

int main() {
    string filename = "Лермонтов.txt";
    string text_to_append = "Волнам их воля и холод дороже\n"
            "Знойных полудня лучей;\n"
            "Люди хотят иметь души… И что же?\n"
            "Души в них волн холодней!\n";

    ofstream file(filename, ios::app);

    if (file.is_open()) {
        file << text_to_append;
        file.close();
    } else {
        cerr << "Не удалось открыть файл для записи." << endl;
    }

    return 0;
}
