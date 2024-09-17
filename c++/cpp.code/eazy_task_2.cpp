#include <iostream>
using namespace std;
int main()
{
    short a, b;

    cin >> a >> b;
    int result = b - a;
    cout << "Расстояние равно " << abs(result);
}