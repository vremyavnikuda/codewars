#include <stdlib.h>
int assignEdgeWeights(int **edges, int edgesSize, int *edgesColSize)
{
    int v = edgesSize + 1, i = 0, u, w, x = 0, y = 1000000007;
    long long a = 2, b = 1;
    int *d = (int *)calloc(v + 1, 4);
    for (; i < edgesSize; i++)
        d[edges[i][0]]++, d[edges[i][1]]++;
    int **g = (int **)malloc(8 * (v + 1));
    int *p = (int *)malloc(4 * (2 * edgesSize + 1)), *t = p;
    for (i = 1; i <= v; i++)
        g[i] = t, t += d[i];
    int *c = (int *)calloc(v + 1, 4);
    for (i = 0; i < edgesSize; i++)
        u = edges[i][0], w = edges[i][1], g[u][c[u]++] = w, g[w][c[w]++] = u;
    free(c);
    int *S = (int *)malloc(4 * (v + 1)), *h = (int *)malloc(4 * (v + 1));
    for (i = 1; i <= v; i++)
        h[i] = -1;
    h[1] = 0;
    int *q = S;
    *q++ = 1;
    while (q > S)
    {
        u = *--q;
        for (i = 0; i < d[u]; i++)
        {
            w = g[u][i];
            if (h[w] == -1)
                h[w] = h[u] + 1, *q++ = w, x = h[w] > x ? h[w] : x;
        }
    }
    free(d);
    free(g);
    free(p);
    free(S);
    free(h);
    if (!x)
        return 1;
    for (x--; x; x >>= 1, a = a * a % y)
        if (x & 1)
            b = b * a % y;
    return (int)b;
}