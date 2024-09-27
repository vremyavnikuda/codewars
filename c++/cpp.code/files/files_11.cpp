#include <iostream>
//
// Created by vremyavnikuda on 9/27/24.
//
using namespace std;
#include <fstream>
//45 числе фибоначи записать в файл
int main() {
    ofstream fibo_text_file("Исследование/Мания Фибоначчи.txt", ios::app);

    if (fibo_text_file.is_open()) {
        int a = 0, b = 1, result;
        fibo_text_file << a << " ";
        for (int i = 1; i < 45; i++) {
            fibo_text_file << b << " ";
            result = a + b;
            a = b;
            b = result;
        }
        fibo_text_file.close();
    } else {
        cerr << "Ошибка при открытии файла!" << endl;
    }
    return 0;
}
