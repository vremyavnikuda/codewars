#include <stdlib.h>

static void swap_int(int *a, int *b)
{
    int t = *a;
    *a = *b;
    *b = t;
}

static int cmp_desc(const void *a, const void *b)
{
    int x = *(const int *)a, y = *(const int *)b;
    return (y > x) - (y < x);
}

static void select_desc(int *a, int n, int need)
{
    int l = 0, r = n - 1, target = need - 1;
    if (need <= 0 || need >= n)
        return;
    while (l < r)
    {
        int m = l + ((r - l) >> 1), i = l, j = r, p;
        if (a[l] < a[m])
            swap_int(a + l, a + m);
        if (a[l] < a[r])
            swap_int(a + l, a + r);
        if (a[m] < a[r])
            swap_int(a + m, a + r);
        p = a[m];
        while (i <= j)
        {
            while (a[i] > p)
                ++i;
            while (a[j] < p)
                --j;
            if (i <= j)
                swap_int(a + i++, a + j--);
        }
        if (target <= j)
            r = j;
        else if (target >= i)
            l = i;
        else
            return;
    }
}

long long maxSum(int *nums, int numsSize, int k, int mul)
{
    long long ans = 0;
    int boosted, i;
    if (numsSize <= 0 || k <= 0)
        return 0;
    if (k < numsSize)
        select_desc(nums, numsSize, k);
    for (i = 0; i < k; ++i)
        ans += nums[i];
    boosted = mul > 1 ? mul - 1 : 0;
    if (boosted > k)
        boosted = k;
    if (boosted > 0)
    {
        select_desc(nums, k, boosted);
        qsort(nums, (size_t)boosted, sizeof(*nums), cmp_desc);
        for (i = 0; i < boosted; ++i)
            ans += (long long)nums[i] * ((long long)mul - i - 1);
    }
    return ans;
}
