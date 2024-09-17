#include <iostream>
using namespace std;
int main()
{
    int x = 4;
    int y = 10;
    int z = -3;

    bool result_1 = x == y - 10 || -z != 3;
    bool result_2 = x> 0 && x<10;
    bool result_3 = !(x!=4);
    bool result_4 = !(x==4 && y==10);
    bool result_5 = y%2==0 &&x%2!=0;
    bool result_6 = x<0 || z<0;
    cout <<boolalpha;
    cout << result_1<<endl;
    cout << result_2<<endl;
    cout << result_3<<endl;
    cout << result_4<<endl;
    cout << result_5<<endl;
    cout << result_6<<endl;
}