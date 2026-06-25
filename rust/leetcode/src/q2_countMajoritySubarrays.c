int countMajoritySubarrays(int *nums, int numsSize, int target)
{
    int n = numsSize, O = 0, p = 0, *b = calloc(2 * n + 3, sizeof(int));
#define _(i, v)                \
    do                         \
    {                          \
        int x = i;             \
        while (x <= 2 * n + 2) \
        {                      \
            b[x] += v;         \
            x += x & -x;       \
        }                      \
    } while (0)
#define __(i) ({int x=i,s=0;while(x){s+=b[x];x-=x&-x;}s; })
    _(n + 1, 1);
    for (int i = 0; i < n; ++i)
    {
        p += (nums[i] == target) ? 1 : -1;
        O += __(p + n);
        _(p + n + 1, 1);
    }
    free(b);
    return O;
}
