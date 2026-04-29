long long maximumScore(int **grid, int gridSize, int *gridColSize)
{
    int n = gridSize, i, j;
    long long a[n + 1], b[n + 1], c[n + 1], e[n + 1], *p = a, *r = c, *t, x, y, z;
    (void)gridColSize;
    for (i = 0; i <= n; ++i)
        p[i] = b[i] = e[i] = 0;
    for (i = 0; i < n; ++i)
        e[i + 1] = e[i] + grid[i][0];
    for (j = 1; j < n; ++j)
    {
        x = 0;
        for (i = 0; i <= n; ++i)
        {
            r[i] = x + e[i];
            z = b[i] - e[i];
            b[i] = r[i];
            if (z > x)
                x = z;
        }
        e[0] = 0;
        for (i = 0; i < n; ++i)
            e[i + 1] = e[i] + grid[i][j];
        x = y = 0;
        for (i = n; i >= 0; --i)
        {
            z = p[i] + e[i];
            if (z > x)
                x = z;
            if (p[i] > y)
                y = p[i];
            z = x - e[i];
            if (z > r[i])
                r[i] = z;
            if (y > b[i])
                b[i] = y;
        }
        t = p, p = r, r = t;
    }
    for (x = 0, i = 0; i <= n; ++i)
        if (p[i] > x)
            x = p[i];
    return x;
}
