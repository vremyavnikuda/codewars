#include <vector>
#include <iostream>
#include <bits/stdc++.h>
using namespace std;

// метод вывода массива данных
int println(vector<int> number)
{
    for (int i : number)
    {
        cout << i << endl;
    }
    return 0;
}

//функция для сортировки массива на убывание.
//параметр greater<int>() -> служит для сортировки массива на убывание.
int sort_vec(vector<int> number)
{
    sort(number.begin(), number.end(),greater<int>());
    println(number);
    return 0;
}
int sum_variable(int a,int b){
    int result;
    if (a!=0 &&b!=0){
        result = a+b;
        return result;
        cout<<result<<endl;
    }else{
        return 0;
    }
}
int main()
{
    vector<int> number;

    number.push_back(10);
    number.push_back(20);
    number.push_back(30);
    number.push_back(40);
    number.push_back(50);
    number.push_back(60);

    println(number);
    sort_vec(number);
    cout<< sum_variable(1,2)<<endl;
    return 0;
}
