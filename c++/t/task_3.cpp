#include <bits/stdc++.h>
using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    unsigned long long a, b;
    if (!(cin >> a >> b))
        return 0;
    int c = 0;
    unsigned long long d = 0;
    while (true)
    {
        d += 1;
        if (a == 0)
        {
            break;
        }
        unsigned long long e = 1ULL << (a - 1);
        bool a_A = (c == 0);
        bool b_B = (b <= e);

        bool a_1 = (a_A ? b_B : !b_B);

        if (a_1)
        {
            if (!a_A)
            {
                b -= e;
            }
            c ^= 1;
            a -= 1;
        }
        else
        {
            d += ((1ULL << a) - 1);

            if (a_A)
            {
                b -= e;
            }
            else
            {
            }
            a -= 1;
        }
    }

    cout << d << "\n";
    return 0;
}
