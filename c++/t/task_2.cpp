#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

vector<int> pa, ra;

void m_(int a)
{
    pa[a] = a;
    ra[a] = 0;
}

int f_(int a)
{
    if (a == pa[a])
        return a;
    return pa[a] = f_(pa[a]);
}

void u_(int s, int r)
{
    s = f_(s);
    r = f_(r);
    if (s != r)
    {
        if (ra[s] < ra[r])
            swap(s, r);
        pa[r] = s;
        if (ra[s] == ra[r])
            ra[s]++;
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<int> e(n + 1);
    for (int i = 1; i <= n; i++)
    {
        cin >> e[i];
    }
    int m;
    cin >> m;
    pa.resize(n + 1);
    ra.resize(n + 1);
    for (int i = 1; i <= n; i++)
    {
        m_(i);
    }
    for (int i = 0; i < m; i++)
    {
        int u, v;
        cin >> u >> v;
        u_(u, v);
    }
    vector<long long> c_m(n + 1, LLONG_MAX);
    for (int i = 1; i <= n; i++)
    {
        int r = f_(i);
        c_m[r] = min(c_m[r], (long long)e[i]);
    }
    long long ans = 0;
    for (int i = 1; i <= n; i++)
    {
        if (c_m[i] != LLONG_MAX)
        {
            ans += c_m[i];
        }
    }
    cout << ans << endl;
    return 0;
}