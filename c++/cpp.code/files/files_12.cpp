#include <iostream>
#include <string>
#include <fstream>
using namespace std;

// Функция для печати файла
// НЕ ИЗМЕНЯТЬ!
void print_file(string filename) {
    ifstream myfile(filename, ios::ate);

    if (!myfile) {
        cerr << "Ошибка при открытии файла для чтения!" << endl;
        return;
    }

    int size = myfile.tellg();
    myfile.seekg(0);

    char content[size + 1]; // +1 для нулевого символа
    myfile.read(content, size);
    content[size] = '\0'; // добавляем нулевой символ

    cout.write(content, size);
}

// Функция для замены текста
void replace_text(string filename, string text, int pos) {
    // Открываем файл для чтения и записи
    fstream file(filename, ios::in | ios::out);

    // Проверка на успешное открытие файла
    if (!file) {
        cerr << "Ошибка при открытии файла!" << endl;
        return;
    }

    // Перемещаем указатель на нужную позицию
    file.seekp(pos);

    // Записываем новый текст
    file << text;

    // Закрываем файл
    file.close();
}

// НЕ ИЗМЕНЯТЬ!
int main() {
    // Ввод данных
    string filename;
    getline(cin, filename);

    string text;
    getline(cin, text);

    int pos;
    cin >> pos;

    // Вызов твоей функции
    replace_text(filename, text, pos);

    // Вывод ответа
    print_file(filename);
}
