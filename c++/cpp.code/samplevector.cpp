#include <vector>
#include <iostream>
using namespace std;
int main(){
    vector<int>number;
    
    number.push_back(10);
    number.push_back(10);
    number.push_back(20);
    number.push_back(30);
    number.push_back(40);
    number.push_back(50);
    number.push_back(60);
    
    for (int i : number){
        cout<<i<<endl;
    }
    return 0;
}