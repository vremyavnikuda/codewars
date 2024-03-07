/*  Задача 8
    Напечатать число наоборот
*/

#include <iostream>

using namespace std;

int Perevor (int n){
    //напечатать числа наоборот
    if (n < 10){
        cout << n;
    }
    else{
        cout << n % 10;
        Perevor(n / 10);
        return 0;
    }
    return 0;
}
int main(){
    int n;
    cin >> n;
    Perevor(n);
}