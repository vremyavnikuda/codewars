#include <iostream>
using namespace std;
int main (){
    int a;
    cin >> a;
    if (a<=0){
        cout<<"Скорость ветра не может быть меньше 0, данные не верны"<<endl;
    }else{
        cout<<"Скорость ветра = "<<a<<endl;
    }
}