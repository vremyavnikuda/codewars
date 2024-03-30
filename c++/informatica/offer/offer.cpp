#include <iostream>

int main() {
    for (int i = 1; i <= 10; ++i) {
        int square = i * i;

        if (square == 25) {
            std::cout << "Квадрат числа " << i << " равен 25. Прерываем выполнение цикла." << std::endl;
            break;
        }

        if (square < 25) {
            std::cout << "Квадрат числа " << i << " равен " << square << std::endl;
            continue;
        }
    }
    return 0;
}
