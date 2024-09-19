#include <iostream>
using namespace std;
int main (){
    int age, money;
    cin >> age>>money;
    
    if (age<=6 || money>=300){
        cout<<"ДА";
    }else{
        cout<<"НЕТ";
    }
}