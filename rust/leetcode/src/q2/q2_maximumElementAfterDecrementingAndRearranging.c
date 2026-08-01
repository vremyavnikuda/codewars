#include <stdlib.h>

static int cmp_int(const void *a, const void *b)
{
    int x = *(const int *)a, y = *(const int *)b;
    return (x > y) - (x < y);
}

int maximumElementAfterDecrementingAndRearranging(int *arr, int arrSize)
{
    int *cnt, ans = 0, i;
    if (arrSize <= 0)
        return 0;
    cnt = (int *)calloc((size_t)arrSize + 1u, sizeof(*cnt));
    if (!cnt)
    {
        qsort(arr, (size_t)arrSize, sizeof(*arr), cmp_int);
        ans = 1;
        for (i = 1; i < arrSize; ++i)
            if (arr[i] > ans)
                ++ans;
        return ans;
    }
    for (i = 0; i < arrSize; ++i)
    {
        int v = arr[i];
        if (v > arrSize)
            v = arrSize;
        ++cnt[v];
    }
    for (i = 1; i <= arrSize; ++i)
    {
        ans += cnt[i];
        if (ans > i)
            ans = i;
    }
    free(cnt);
    return ans;
}
