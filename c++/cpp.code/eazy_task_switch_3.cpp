#include <iostream>
using namespace std;
int main()
{
    char exp;
    float num_1, num_2;
    cin >> num_1 >> exp >> num_2;

    switch (exp)
    {
    case '+':
        cout << num_1 + num_2;
        break;

    case '-':
        cout << num_1 - num_2;
        break;

    case '*':
        cout << num_1 * num_2;
        break;

    case '/':
        if (num_2 != 0)
        {
            cout << num_1 / num_2;
            break;
        }else{
            cout << "На ноль делить нельзя";
            break;
        }
    }
}