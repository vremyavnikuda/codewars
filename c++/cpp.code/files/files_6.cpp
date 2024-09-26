#include <fstream>
#include <iostream>
#include <string>
//
// Created by vremyavnikuda on 9/26/24.
//
/*
2. Читаем отрывками
Проходя курсы, очень важно научиться читать и понимать задания. Даже если не получается одним глотком всё прочитать и осознать, нужно хотя бы пытаться делать это малыми отрывками.

Как тебе идея написать программу, которая поможет тебе научиться читать задания?

Задание: Напиши программу, которая открывает файл Задание 6-2-4.txt и читает из него определённую часть (см. секцию Входные данные).

Входные данные
Программе на вход подаётся номер первого символа, который нужно прочитать, и количество байт, которые нужно прочитать после этого символа.

Выходные данные
Программа должна вывести содержимое обозначенной части.

Используй методы .seekg и .read!
*/
using namespace std;

int main() {
    int position, size_byte;
    cin >> position >> size_byte;

    ifstream text("Задание 6-2-4.txt");

    if (text.is_open()) {
        text.seekg(position);
        string result(size_byte, '\0');
        text.read(&result[0], size_byte);
        result.resize(text.gcount());
        cout << result << endl;
        text.close();
    } else {
        cerr << "Ошибка: не удалось открыть файл." << endl;
    }
    return 0;
}

/*
int main()
{
    ifstream file("Задание 6-2-4.txt");

    int a{},b{};
    cin >> a >> b;
    char out[b+1]{};
    file.seekg(a);
    file.read(out,b);
    cout << out;
}
*/
