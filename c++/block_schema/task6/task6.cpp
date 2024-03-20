#include <iostream>
//Задача 6
// Функция, печатающая текст в обратном порядке

void Revers(){
    char ch;
    //Получаем данные от пользователя
    std::cin >> ch;
    //Вызываем рекурсию и выводим символ
    if (ch == '.')
        return;
    else
        Revers();
    std::cout << ch;
}

int main(){
    // Вызов функции для печати текста в обратном порядке
    Revers();               
    std::cout << std::endl;
    return 0;
}
