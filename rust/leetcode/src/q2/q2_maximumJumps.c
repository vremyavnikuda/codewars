int maximumJumps(int *nums, int numsSize, int target)
{
    int *d = (int *)malloc(numsSize * sizeof(int)), x, i, j, g;
    for (i = 0; i < numsSize; i++)
        d[i] = -1;
    d[numsSize - 1] = 0;
    for (i = numsSize - 2; i >= 0; i--)
    {
        x = -1;
        for (j = i + 1; j < numsSize; j++)
        {
            g = nums[j] - nums[i];
            if (g < 0)
                g = -g;
            if (g <= target && d[j] >= 0)
            {
                g = d[j] + 1;
                x = g > x ? g : x;
            }
        }
        d[i] = x;
    }
    x = d[0];
    free(d);
    return x;
}