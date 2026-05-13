#include <stdlib.h>

int minMoves(int *nums, int numsSize, int limit)
{
    int m = limit << 1, *d = (int *)calloc((size_t)m + 2u, sizeof(*d)), s = 0, a = numsSize, x, y, t, i;
    int *l = nums, *r = nums + numsSize - 1;
    if (!d)
        return 0;
    for (; l < r; ++l, --r)
        x = *l, y = *r, x > y ? (t = x, x = y, y = t, 0) : 0,
        d[2] += 2, --d[x + 1], --d[x + y], ++d[x + y + 1], ++d[y + limit + 1];
    for (i = 2; i <= m; ++i)
        a = a < (s += d[i]) ? a : s;
    free(d);
    return a;
}
