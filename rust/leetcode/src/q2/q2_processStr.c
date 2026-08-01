#include <stdlib.h>
#include <string.h>

char *processStr(char *s)
{
    char *r = 0;
    size_t n = 0, c = 0;
    char *p = s;
    if (!p)
        goto Z;
J:
    if (!*p)
        goto Z;
    unsigned _ = *p;
    if ((_ | 32) - 97U < 26U)
        goto A;
    if (_ == 42)
        goto B;
    if (_ == 35)
        goto C;
    if (_ == 37)
        goto D;
    goto E;
A:
    if (n == c)
    {
        c = c ? c * 2 : 1;
        r = realloc(r, c + 1);
    }
    r[n++] = _;
    goto E;
B:
    n -= !!n;
    goto E;
C:
    if (n)
    {
        if (n * 2 > c)
        {
            c = n * 2;
            r = realloc(r, c + 1);
        }
        memcpy(r + n, r, n);
        n *= 2;
    }
    goto E;
D:
    if (n)
    {
        size_t i = 0, j = n - 1;
    W:
        if (i >= j)
            goto E;
        char t = r[i];
        r[i] = r[j];
        r[j] = t;
        i++;
        j--;
        goto W;
    }
E:
    p++;
    goto J;
Z:
    r = r ? realloc(r, n + 1) : calloc(n + 1, 1);
    r[n] = 0;
    return r;
}