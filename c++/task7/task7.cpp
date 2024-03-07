/*  Задача 7
    Вводится последовательность ненулевых целых чисел, за которой следует 0. Напечатать сначала все 
    отрицательные числа этой последовательности, а затем – все положительные (в любом порядке).
    7 12 -4 -10 3 -1 2 5 90 0
*/
#include <iostream>

void Chisla() {
    int a;
    std::cin >> a;

    if (a == 0)
        return;

    if (a < 0) {
        std::cout << a << std::endl;
        Chisla();
    }
    else {
        Chisla();
        std::cout << a << std::endl;
    }

    return;
}

int main() {
    Chisla();
    return 0;
}
