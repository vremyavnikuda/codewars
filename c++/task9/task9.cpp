/*
Задача 9
Определить рекурсивную функцию для преобразования числа n из десятичной системы счисления в 
любую другую, используя многократное деление на еѐ основание k.
*/

#include <iostream>

using namespace std;

int Perevor (int n, int k){
    //напечатать числа наоборот
    if (n < k){
        cout << n;
    }
    else{
        cout << n % k;
        Perevor(n / k, k);
        return 0;
    }
    return 0;
}
int main(){
    int n, k;
    cin >> n >> k;
    Perevor(n, k);
}