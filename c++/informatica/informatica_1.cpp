#include <iostream>

/*
Вариант а 
условный оператор if-else if-else

Определить номер четверти плоскости, в которой находится точка с координатами х и у (х*у ≠ 0).

Данный код запрашивает у пользователя ввод двух чисел ,которые представляют собой координаты точки 
плоскости (x,y)

Определяет ,в какой четверти координатной плоскости находится эта точка и выводит соответствующее сообщение
Если x > 0 и y > 0, то точка находится в первой четверти.
Если x < 0 и y > 0, то точка находится во второй четверти.
Если x < 0 и y < 0, то точка находится в третьей четверти.
Если x > 0 и y < 0, то точка находится в четвертой четверти.
Если ни одно из этих условий не выполняется, то точка находится на оси, то есть не в четверти.
*/

void variantA(int x, int y) {
    if (x > 0 && y > 0) {
        std::cout << "The point is in the first quarter.";
    } else if (x < 0 && y > 0) {
        std::cout << "The point is in the second quarter.";
    } else if (x < 0 && y < 0) {
        std::cout << "The point is in the third quarter.";
    } else if (x > 0 && y < 0) {
        std::cout << "The point is in the fourth quarter.";
    } else {
        std::cout << "The point is on the axis, not in the quarter.";
    }
}

/*
Вариант б
Тернарная операция
Определить номер четверти плоскости, в которой находится точка с координатами х и у (х*у ≠ 0).

Данный код запрашивает у пользователя ввод двух чисел ,которые представляют собой координаты точки 
плоскости (x,y)

Определяет ,в какой четверти координатной плоскости находится эта точка и выводит соответствующее сообщение
Если x > 0 и y > 0, то точка находится в первой четверти.
Если x < 0 и y > 0, то точка находится во второй четверти.
Если x < 0 и y < 0, то точка находится в третьей четверти.
Если x > 0 и y < 0, то точка находится в четвертой четверти.
Если ни одно из этих условий не выполняется, то точка находится на оси, то есть не в четверти.
*/

void variantB(int x, int y) {
    std::cout << (x > 0 && y > 0 ? "The point is in the first quarter."
                : x < 0 && y > 0 ? "The point is in the second quarter."
                : x < 0 && y < 0 ? "The point is in the third quarter."
                : x > 0 && y < 0 ? "The point is in the fourth quarter."
                : "The point is on the axis, not in the quarter.");
}

int main() {
    int x, y;
    std::cout << "Enter the x and y coordinates: ";
    std::cin >> x >> y;

    std::cout << "Variant A: ";
    variantA(x, y);

    std::cout << "\nVariant B: ";
    variantB(x, y);

    return 0;
}