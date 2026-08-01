#include <vector>
#include <cstring>
#include <algorithm>
using namespace std;
class Solution
{
public:
    int maxJumps(vector<int> &a, int d)
    {
        int n = a.size(), f[n], o[n], i, j, v, x = 1;
        memset(f, 0, sizeof f);
        for (i = n; i--; o[i] = i)
            ;
        sort(o, o + n, [&](int p, int q)
             { return a[p] < a[q]; });
        for (int _ = 0; _ < n; ++_)
        {
            i = o[_];
            j = i;
            v = 1;
            while (0 < j-- && j >= i - d && a[j] < a[i])
                v = max(v, 1 + f[j]);
            j = i;
            while (++j < n && j <= i + d && a[j] < a[i])
                v = max(v, 1 + f[j]);
            x = max(x, f[i] = v);
        }
        return x;
    }
};
