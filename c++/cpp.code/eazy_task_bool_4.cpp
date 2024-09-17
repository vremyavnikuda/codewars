#include <iostream>
using namespace std;

int main()
{
    int a, b, c;
    cin >> a >> b >> c;

    if ((a + b > c) && (b + c > a) && (c + a > b))
    {
        cout << "ДА" << endl;
    }
    else
    {
        cout << "НЕТ" << endl;
    }

    return 0;
}
