/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
#include <stdlib.h>

#define Z(a, b) ((a) < (b) ? (a) : (b))
#define Y(x)        \
    do              \
    {               \
        *(x) = r[c++]; \
        if (c == L) \
            c = 0;  \
    } while (0)

int **rotateGrid(int **grid, int gridSize, int *gridColSize, int k, int *returnSize, int **returnColumnSizes)
{
    int a = gridSize, b = (a && gridColSize) ? gridColSize[0] : 0, p, i, j;

    *returnSize = a;
    *returnColumnSizes =
        a ? (int *)malloc((size_t)a * sizeof(**returnColumnSizes)) : 0;
    if (a && !*returnColumnSizes)
    {
        *returnSize = 0;
        return 0;
    }
    for (i = 0; i < a; ++i)
        (*returnColumnSizes)[i] = gridColSize ? gridColSize[i] : b;

    if (grid && a > 1 && b > 1)
    {
        int r[((a + b) << 1) ? ((a + b) << 1) : 1];
        for (p = 0; p < Z(a, b) / 2; ++p)
        {
            int R = b - p - 1, B = a - p - 1, L = ((R - p) + (B - p)) << 1;
            int K = k % L, t = 0, c;

            if (K < 0)
                K += L;
            if (!K)
                continue;

            for (j = p; j < R; ++j)
                r[t++] = grid[p][j];
            for (i = p; i < B; ++i)
                r[t++] = grid[i][R];
            for (j = R; j > p; --j)
                r[t++] = grid[B][j];
            for (i = B; i > p; --i)
                r[t++] = grid[i][p];

            c = K;
            for (j = p; j < R; ++j)
                Y(grid[p] + j);
            for (i = p; i < B; ++i)
                Y(grid[i] + R);
            for (j = R; j > p; --j)
                Y(grid[B] + j);
            for (i = B; i > p; --i)
                Y(grid[i] + p);
        }
    }

    return grid;
}
