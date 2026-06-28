/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
#include <stdlib.h>

static int cmp_interval(const void *a, const void *b)
{
    const int *x = *(const int *const *)a;
    const int *y = *(const int *const *)b;
    if (x[0] != y[0])
        return x[0] < y[0] ? -1 : 1;
    if (x[1] != y[1])
        return x[1] < y[1] ? -1 : 1;
    return 0;
}

static void add_interval(int **ans, int *cols, int *size, int left, int right)
{
    int *row = (int *)malloc(2 * sizeof(*row));
    row[0] = left;
    row[1] = right;
    ans[*size] = row;
    cols[*size] = 2;
    ++*size;
}

int **filterOccupiedIntervals(int **occupiedIntervals, int occupiedIntervalsSize, int *occupiedIntervalsColSize, int freeStart, int freeEnd, int *returnSize, int **returnColumnSizes)
{
    int **ans;
    int *cols;
    int i, left, right;
    (void)occupiedIntervalsColSize;
    *returnSize = 0;
    ans = (int **)malloc(((size_t)occupiedIntervalsSize + 1u) * sizeof(*ans));
    cols = (int *)malloc(((size_t)occupiedIntervalsSize + 1u) * sizeof(*cols));
    *returnColumnSizes = cols;
    if (occupiedIntervalsSize <= 0)
        return ans;
    qsort(occupiedIntervals, (size_t)occupiedIntervalsSize, sizeof(*occupiedIntervals), cmp_interval);
    left = occupiedIntervals[0][0];
    right = occupiedIntervals[0][1];
    for (i = 1; i < occupiedIntervalsSize; ++i)
    {
        int a = occupiedIntervals[i][0], b = occupiedIntervals[i][1];
        if (a <= right + 1)
        {
            if (b > right)
                right = b;
        }
        else
        {
            if (left < freeStart)
                add_interval(ans, cols, returnSize, left, right < freeStart ? right : freeStart - 1);
            if (right > freeEnd)
                add_interval(ans, cols, returnSize, left > freeEnd ? left : freeEnd + 1, right);
            left = a;
            right = b;
        }
    }
    if (left < freeStart)
        add_interval(ans, cols, returnSize, left, right < freeStart ? right : freeStart - 1);
    if (right > freeEnd)
        add_interval(ans, cols, returnSize, left > freeEnd ? left : freeEnd + 1, right);
    return ans;
}
