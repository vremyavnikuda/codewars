#include <stdlib.h>
typedef int _;
_ __(const void *a, const void *b) { return (*(_ **)a)[0] - (*(_ **)b)[0]; }
_ maxBuilding(_ n, _ **r, _ s, _ *c)
{
    _ i, j, k, l, m, o, p, e;
    (void)c;
    if (!s)
        return n - 1;
    qsort(r, s, sizeof(_ *), __);
    j = 1;
    k = 0;
    for (i = 0; i < s; i++)
        l = k + r[i][0] - j, r[i][1] = r[i][1] < l ? r[i][1] : l, j = r[i][0], k = r[i][1];
    if (r[s - 1][0] == n)
    {
        e = r[s - 1][1];
        m = s - 2;
    }
    else
    {
        e = n - 1 < r[s - 1][1] + n - r[s - 1][0] ? n - 1 : r[s - 1][1] + n - r[s - 1][0];
        m = s - 1;
    }
    j = n;
    k = e;
    for (i = m; i >= 0; i--)
        l = k + j - r[i][0], r[i][1] = r[i][1] < l ? r[i][1] : l, j = r[i][0], k = r[i][1];
    j = 1;
    k = 0;
    o = 0;
    for (i = 0; i < s; i++)
        p = (k + r[i][1] + r[i][0] - j) / 2, o = o < p ? p : o, j = r[i][0], k = r[i][1];
    if (r[s - 1][0] != n)
        p = (k + e + n - j) / 2, o = o < p ? p : o;
    return o;
}