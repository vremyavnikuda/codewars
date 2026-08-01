#include <stdlib.h>
#define H(i) ((unsigned long long)(i) >> 32 ^ (unsigned long long)(i))
int maximumLength(int *nums, int numsSize)
{
    int a = 0, b, c = 0, d = 0, e;
    long long i, j;
    if (!numsSize)
        return 0;
    e = numsSize * 2 - 1;
    e |= e >> 1;
    e |= e >> 2;
    e |= e >> 4;
    e |= e >> 8;
    e |= e >> 16;
    struct
    {
        long long x;
        int y;
    } *p = calloc(e + 1, sizeof(*p));
    if (!p)
        return 0;
    for (; a < numsSize; a++)
    {
        i = nums[a];
        b = H(i) & e;
        while (p[b].y)
        {
            if (p[b].x == i)
            {
                p[b].y++;
                goto L0;
            }
            b = b + 1 & e;
        }
        p[b].x = i;
        p[b].y = 1;
    L0:;
    }
    for (b = 1 & e; p[b].y && p[b].x != 1; b = b + 1 & e)
        ;
    if (p[b].y)
        d = p[b].y - (p[b].y % 2 ^ 1);
    for (a = 0; a <= e; a++)
    {
        if (!p[a].y || p[a].x == 1)
            continue;
        c = 0;
        i = p[a].x;
        while (1)
        {
            j = i;
            b = H(j) & e;
            while (p[b].y && p[b].x != j)
                b = b + 1 & e;
            if (!p[b].y || p[b].y < 2)
            {
                c += p[b].y ? 1 : -1;
                break;
            }
            c += 2;
            i *= i;
            if (i <= 1)
            {
                c--;
                break;
            }
        }
        if (c > d)
            d = c;
    }
    free(p);
    return d;
}