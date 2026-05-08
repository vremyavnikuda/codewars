#include <stdlib.h>
#include <string.h>

#define Z 1000000
#define O(x) ((c[(x) >> 3] >> ((x) & 7)) & 1)
#define I(x) (c[(x) >> 3] |= (unsigned char)(1u << ((x) & 7)))

static int *w;

static void f(void)
{
    int i, j;
    if (w)
        return;
    w = (int *)calloc((size_t)Z + 1u, sizeof(*w));
    if (!w)
        return;
    for (i = 2; i <= Z; ++i)
        if (!w[i])
        {
            w[i] = i;
            if ((long long)i * i <= Z)
                for (j = i * i; j <= Z; j += i)
                    if (!w[j])
                        w[j] = i;
        }
}

int minJumps(int* nums, int numsSize)
{
    int n = numsSize, m = 0, z = 0, i, x, y, p, k = 0;
    int *h, *to, *nx, *q, l = 0, r = 0, a = 0;
    unsigned char *c;
    if (n < 2)
        return 0;
    for (i = 0; i < n; ++i)
        if (nums[i] > m)
            m = nums[i];
    if (m > Z)
        return -1;
    f();
    if (!w)
        return -1;
    for (i = 0; i < n; ++i)
        for (y = nums[i]; y > 1;)
        {
            p = w[y];
            ++z;
            do
            {
                y /= p;
            } while (y > 1 && w[y] == p);
        }
    h = (int *)malloc(((size_t)m + 1u) * sizeof(*h));
    to = z ? (int *)malloc((size_t)z * sizeof(*to)) : 0;
    nx = z ? (int *)malloc((size_t)z * sizeof(*nx)) : 0;
    q = (int *)malloc((size_t)n * sizeof(*q));
    c = (unsigned char *)calloc(((size_t)n + 7u) >> 3, 1);
    if (!h || !q || !c || (z && (!to || !nx)))
    {
        free(h);
        free(to);
        free(nx);
        free(q);
        free(c);
        return -1;
    }
    memset(h, 255, ((size_t)m + 1u) * sizeof(*h));
    for (i = 0; i < n; ++i)
        for (y = nums[i]; y > 1;)
        {
            p = w[y];
            to[k] = i;
            nx[k] = h[p];
            h[p] = k++;
            do
            {
                y /= p;
            } while (y > 1 && w[y] == p);
        }
    q[r++] = 0;
    I(0);
    while (l < r)
    {
        int e = r;
        while (l < e)
        {
            i = q[l++];
            if (i == n - 1)
            {
                free(h);
                free(to);
                free(nx);
                free(q);
                free(c);
                return a;
            }
            x = i + 1;
            if (x < n && !O(x))
            {
                I(x);
                q[r++] = x;
            }
            x = i - 1;
            if (x >= 0 && !O(x))
            {
                I(x);
                q[r++] = x;
            }
            x = nums[i];
            if (x > 1 && w[x] == x)
            {
                for (k = h[x]; k != -1; k = nx[k])
                {
                    y = to[k];
                    if (!O(y))
                    {
                        I(y);
                        q[r++] = y;
                    }
                }
                h[x] = -1;
            }
        }
        ++a;
    }
    free(h);
    free(to);
    free(nx);
    free(q);
    free(c);
    return -1;
}
