/*Задание 8
Напечатать число наоборот.
input: 857496945
output:549694758
*/

#include <iostream>
void Perevor(int n){
    //Если число <10 выводим его  
    if (n < 10){
        std::cout << n;
        return;
    }
    //Условие переворота числа
    else{
        std::cout << n % 10;
        Perevor(n / 10);
        return;
    }
}

int main(){
    int n;
    //Получаем число от пользователя
    std::cin >> n;
    //Вызываем функцию
    Perevor(n);
}