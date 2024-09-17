#include <iostream>
using namespace std;

int main(){
    float num_1,num_2;
    float result;
    cin>>num_1>>num_2;
    if (num_2!=0){
        result=num_1/num_2;
        cout<<result;
    }else{
        cout<<"На ноль делить нельзя";
    }
}