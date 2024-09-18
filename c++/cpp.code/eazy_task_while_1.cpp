#include <iostream>
int main(){
    int i=0;
    int count=0;
    do{
        std::cout<<"До нового года осталось "<<i<<" секунд"<<std::endl;
        i--;
        count++;
    }while(i>0);
    std::cout<<"С Новым годом!!!"<<std::endl;
    std::cout<<count<<std::endl;
}