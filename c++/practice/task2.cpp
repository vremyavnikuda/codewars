#include <iostream>

using namespace std;

// Функция для вычисления квадрата числа n без использования операции умножения
int square(int n, int odd = 1) {
    if (n == 1) {
        return odd;
    }
    return odd + square(n - 1, odd + 2);
}

int main() {
    int n;
    cout << "Введите число n: ";
    cin >> n;
    // Вызываем функцию для вычисления квадрата числа n
    int result = square(n);
    // Выводим результат
    cout << "Квадрат числа " << n << ": " << result << endl;
    return 0;
}
