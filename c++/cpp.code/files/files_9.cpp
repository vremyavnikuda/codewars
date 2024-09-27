#include <fstream>
#include <iostream>
//
// Created by vremyavnikuda on 9/27/24.
//
using namespace std;

void print_file()
{
    ifstream myfile("одуванчики.txt", ios::ate);

    int size = myfile.tellg();
    myfile.seekg(0);

    char content[size];
    myfile.read(content, size);

    // Невероятно, но так тоже можно
    cout.write(content, size);
}


int main() {
    fstream myfile("одуванчики.txt", ios::in | ios::out | ios::app);

    if (!myfile) {
        cerr << "error" << endl;
        return 1;
    }
    string content="С новым 1928 годом!";
    myfile << content << endl;

    myfile.close();
    print_file();
    return 0;
}