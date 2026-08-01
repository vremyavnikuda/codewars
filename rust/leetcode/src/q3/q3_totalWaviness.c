#include <string.h>

/*
 * Problem: totalWaviness(a, b) — sum of "waviness" of all numbers in [a, b].
 * Waviness of a number = count of positions i where digits form a peak or valley:
 *   (d[i-1] > d[i] < d[i+1]) or (d[i-1] < d[i] > d[i+1])
 * for any three consecutive digits.
 *
 * L          — typedef for long long
 * _n         — number of digits of N
 * _d[20]     — digit array of N (most significant first)
 * _mC / _mS  — memo for count / sum per state (pos, pp, pr, st)
 * _mV        — visited flag for memo
 * _tc / _ts  — result of the last _b call (count / sum)
 *
 * _b(pos, pp, pr, st, ti) parameters
 * pos        — current position (index into _d)
 * pp         — digit at position pos-2 (10 = no digit yet)
 * pr         — digit at position pos-1 (10 = no digit yet)
 * st         — 1 if number has started (non-zero digit seen)
 * ti         — 1 if upper bound = _d[pos] (tight)
 *
 * _b local variables
 * h          — max digit at current position (9 or _d[pos] if tight)
 * c / s      — accumulated count / sum for current node
 * d          — current digit being tried (0..h)
 * ns         — st for next step (st || d != 0)
 * npp / np   — pp / pr for next step
 * a          — 1 if triple (pp, pr, d) adds waviness
 *
 * F(N)
 * Extracts digits of N, resets memo, calls _b, returns _ts.
 * Answer: F(b) - F(a-1).
 */
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
