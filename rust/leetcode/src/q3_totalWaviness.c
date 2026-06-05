#include <string.h>
typedef long long L;
static int _n, _d[20];
static L _mC[20][11][11][2], _mS[20][11][11][2];
static char _mV[20][11][11][2], _i;
static L _tc, _ts;
static void _b(int p, int pp, int pr, int st, int ti)
{
    if (p == _n)
    {
        _tc = 1;
        _ts = 0;
        return;
    }
    if (!ti && _mV[p][pp][pr][st])
    {
        _tc = _mC[p][pp][pr][st];
        _ts = _mS[p][pp][pr][st];
        return;
    }
    int h = ti ? _d[p] : 9;
    L c = 0, s = 0;
    for (int d = 0; d <= h; d++)
    {
        int ns = st || d, npp, np;
        L a = 0;
        if (!ns)
        {
            npp = 10;
            np = 10;
        }
        else if (!st)
        {
            npp = 10;
            np = d;
        }
        else
        {
            if (pp != 10 && pr != 10 && ((pr > pp && pr > d) || (pr < pp && pr < d)))
                a = 1;
            npp = pr;
            np = d;
        }
        _b(p + 1, npp, np, ns, ti && d == h);
        c += _tc;
        s += _ts + a * _tc;
    }
    if (!ti)
    {
        _mV[p][pp][pr][st] = 1;
        _mC[p][pp][pr][st] = c;
        _mS[p][pp][pr][st] = s;
    }
    _tc = c;
    _ts = s;
}
static L F(L N)
{
    if (N < 0)
        return 0;
    _n = 0;
    L x = N;
    if (!x)
    {
        _d[_n++] = 0;
    }
    else
    {
        char b[20];
        int l = 0;
        while (x)
        {
            b[l++] = x % 10;
            x /= 10;
        }
        for (int i = l - 1; i >= 0; i--)
            _d[_n++] = b[i];
    }
    memset(_mV, 0, sizeof(_mV));
    _b(0, 10, 10, 0, 1);
    return _ts;
}
long long totalWaviness(long long a, long long b) { return F(b) - F(a - 1); }
