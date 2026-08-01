#include <stdlib.h>
int maxPathScore(int **grid, int gridSize, int *gridColSize, int k)
{
    int z = gridSize, w = *gridColSize, q, N = -1073741824, *p, *x, y, c, i, j, r, a, b, t;
    if (z < 1 || w < 1 || k < 0)
        return -1;
    if (k > z + w - 2)
        k = z + w - 2;
    q = k + 1;
    p = (int *)malloc((size_t)w * q * sizeof(int));
    if (!p)
        return -1;
    for (i = w * q; i--;)
        p[i] = N;
    for (r = q; r--;)
        p[r] = 0;
    for (i = 0; i < z; ++i)
        for (j = 0; j < w; ++j)
        {
            if (!i && !j)
                continue;
            x = p + j * q;
            y = grid[i][j];
            c = !!(y > 0);
            for (r = 0; r < q - c; ++r)
            {
                a = i ? x[r + c] : N;
                b = j ? p[(j - 1) * q + r + c] : N;
                t = a > b ? a : b;
                x[r] = t <= N / 2 ? N : t + y;
            }
            for (; r < q; ++r)
                x[r] = N;
        }
    a = N;
    x = p + (w - 1) * q;
    for (r = 0; r < q; ++r)
        if (x[r] > a)
            a = x[r];
    free(p);
    return a < 0 ? -1 : a;
}
