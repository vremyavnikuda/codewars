#include <fstream>
#include <iostream>
//
// Created by vremyavnikuda on 9/27/24.
//
using namespace std;

// Функция для печати файла
// НЕ ИЗМЕНЯТЬ!
void print_file()
{
    ifstream myfile("hello-world.txt", ios::ate);

    int size = myfile.tellg();
    myfile.seekg(0);

    char content[size];
    myfile.read(content, size);

    cout.write(content, size);
}

int main() {
    ofstream myfile { "hello-world.txt",ios::binary | ios::out | ios::trunc };

    if (!myfile) {
        cerr << "error" << endl;
        return 1;
    }
    char hello[] = "Привет тебе из файла!";
    myfile.write(hello, sizeof(hello)-1);
    myfile.close();
    print_file();
    return 0;
}