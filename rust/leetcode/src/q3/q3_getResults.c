/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
#include <stdlib.h>
#include <stdbool.h>
static int _(const void *a, const void *b) { return *(int *)a - *(int *)b; }
bool *getResults(int **queries, int queriesSize, int *queriesColSize, int *returnSize)
{
    int n = 50000, t = queriesSize * 3, i, j, k = 0, a = 0, x, y, z, u, v, w;
    if (t < n)
        n = t;
    for (i = 0; i < queriesSize; ++i)
        queries[i][0] == 1 ? ++k : ++a;
    *returnSize = a;
    bool *r = malloc((a ? a : 1) * sizeof *r);
    int *f = calloc(n + 3, sizeof *f);
    int *o = malloc((k + 2) * sizeof *o);
    int *L = malloc((k + 2) * sizeof *L);
    int *Q = malloc((k + 2) * sizeof *Q);
    char *d = calloc(k + 2, 1);
    if (!r || !f || !o || !L || !Q || !d)
    {
        *returnSize = 0;
        return 0;
    }
    o[0] = 0;
    for (i = j = 0; i < queriesSize; ++i)
        if (queries[i][0] == 1)
            o[++j] = queries[i][1];
    o[j + 1] = n;
    k = j + 1;
    if (j > 1)
        qsort(o + 1, j, sizeof *o, _);
    for (i = 0; i <= k; ++i)
    {
        L[i] = i - 1;
        Q[i] = i + 1;
    }
    for (i = 0; i < k; ++i)
    {
        x = o[i + 1] - o[i];
        for (j = o[i + 1]; j <= n; j += j & -j)
            if (x > f[j])
                f[j] = x;
    }
    for (i = queriesSize - 1, z = a; i >= 0; --i)
    {
        x = queries[i][1];
        if (queries[i][0] == 1)
        {
            for (u = 1, v = k - 1, w = 0; u <= v;)
            {
                w = (u + v) >> 1;
                if (o[w] < x)
                    u = w + 1;
                else if (o[w] > x)
                    v = w - 1;
                else
                    break;
            }
            y = w;
            d[y] = 1;
            if (Q[y] <= k)
            {
                x = o[Q[y]] - o[L[y]];
                for (j = o[Q[y]]; j <= n; j += j & -j)
                    if (x > f[j])
                        f[j] = x;
            }
            if (L[y] >= 0)
                Q[L[y]] = Q[y];
            if (Q[y] <= k)
                L[Q[y]] = L[y];
        }
        else
        {
            y = queries[i][2];
            for (u = 0, v = k, j = k + 1; u <= v;)
            {
                w = (u + v) >> 1;
                if (o[w] > x)
                {
                    j = w;
                    v = w - 1;
                }
                else
                    u = w + 1;
            }
            if (j > k)
                w = o[k];
            else
            {
                while (d[j])
                    j = Q[j];
                w = o[L[j]];
            }
            for (u = 0, v = w; v; v -= v & -v)
                if (f[v] > u)
                    u = f[v];
            r[--z] = (u >= y) || (x - w >= y);
        }
    }
    free(f);
    free(o);
    free(L);
    free(Q);
    free(d);
    return r;
}