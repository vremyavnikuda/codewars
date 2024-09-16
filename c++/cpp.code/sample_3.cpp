#include <iostream>

int main(){
    int a,b;
    a=3.0;
    b=1.0;
    a=a-b;
    b=b* ++a;
    std::cout<<b<<std::endl;
}