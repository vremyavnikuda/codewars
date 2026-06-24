#include <stdlib.h>

int zigZagArrays(int n, int l, int r)
{
    r -= l;
    int mod = 1000000007, *prefix, *p, *end, i = 1, zig = 1;
    long long result = 0;

    if (r < 1 || !(prefix = malloc(r * sizeof(int))))
        return 0;

    p = prefix;
    end = prefix + r;
    while (p < end)
        *p++ = 1;

    p = prefix + 1;
    while (p < end)
        *p += p[-1], p++;

    for (; i < n - 1; i++)
    {
        if (zig)
        {
            p = prefix + r - 2;
            while (p >= prefix)
                *p += p[1], *p -= *p >= mod ? mod : 0, p--;
        }
        else
        {
            p = prefix + 1;
            while (p < end)
                *p += p[-1], *p -= *p >= mod ? mod : 0, p++;
        }
        zig ^= 1;
    }

    p = prefix;
    while (p < end)
        result += *p++;

    free(prefix);
    return (int)(result * 2 % mod);
}