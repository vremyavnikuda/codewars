/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#define _H(x) ((uint32_t)(x) * 2654435761u)
long long *distance(int *nums, int numsSize, int *returnSize)
{
    int n = numsSize, i, v, m = 1, *k, *c;
    long long *o;
    long long *s;
    unsigned char *u;
    uint32_t p, q;

    if (returnSize)
        *returnSize = n;
    if (n <= 0)
        return (long long *)malloc(0);
    o = (long long *)malloc((size_t)n * sizeof(*o));
    if (!o)
    {
        if (returnSize)
            *returnSize = 0;
        return 0;
    }

    while (m < (n << 1))
        m <<= 1;
    k = (int *)malloc((size_t)m * sizeof(*k));
    c = (int *)malloc((size_t)m * sizeof(*c));
    s = (long long *)malloc((size_t)m * sizeof(*s));
    u = (unsigned char *)calloc((size_t)m, 1);
    if (!k || !c || !s || !u)
    {
        free(u), free(s), free(c), free(k), free(o);
        if (returnSize)
            *returnSize = 0;
        return 0;
    }

    for (i = 0; i < n; ++i)
    {
        v = nums[i], p = _H(v) & (uint32_t)(m - 1);
        while (u[p] && k[p] != v)
            p = (p + 1) & (uint32_t)(m - 1);
        if (!u[p])
            u[p] = 1, k[p] = v, c[p] = 0, s[p] = 0;
        o[i] = (long long)i * c[p] - s[p], ++c[p], s[p] += i;
    }

    memset(u, 0, (size_t)m);
    for (i = n - 1; i >= 0; --i)
    {
        v = nums[i], q = _H(v) & (uint32_t)(m - 1);
        while (u[q] && k[q] != v)
            q = (q + 1) & (uint32_t)(m - 1);
        if (!u[q])
            u[q] = 1, k[q] = v, c[q] = 0, s[q] = 0;
        o[i] += s[q] - (long long)i * c[q], ++c[q], s[q] += i;
    }

    free(u), free(s), free(c), free(k);
    return o;
}
#undef _H
