int minOperations(int **grid, int gridSize, int *gridColSize, int x)
{
    int a[10001] = {0}, b = *gridColSize, c = gridSize * b, d = grid[0][0] % x, e, f, g, h = 0, i = 0, j = 0;
    for (; i < gridSize; i++)
        for (j = 0; j < b; j++)
        {
            e = grid[i][j];
            if (e % x != d)
                return -1;
            ++a[e];
        }
    for (e = 0; h <= c / 2; h += a[e++])
        ;
    g = e - 1;
    for (e = 0, j = 0; e < 10001; e++)
        if (a[e])
        {
            f = e - g;
            if (f < 0)
                f = -f;
            j += a[e] * (f / x);
        }
    return j;
}
