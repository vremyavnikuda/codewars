#include <iostream>

using namespace std;

int task2(int a, int b) {
    if (b == 0) return 1;
    return a * task2(a, b - 1);
}

int main() {
    int a, b;
    cout << "Введите число a: ";
    cin >> a;
    cout << "Введите степень b: ";
    cin >> b;
    cout << a << " в степени " << b << " равно " << task2(a, b) << endl;
    return 0;
}
