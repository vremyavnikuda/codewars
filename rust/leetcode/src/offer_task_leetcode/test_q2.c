#include <stdio.h>
#include <stdlib.h>

int maximumJumps(int *nums, int numsSize, int target);

int main()
{
    int nums[] = {0, 2, 4, 6, 8};
    int r = maximumJumps(nums, 5, 3);
    printf("Test1: %d\n", r);

    int nums2[] = {1, 1, 1};
    r = maximumJumps(nums2, 3, 0);
    printf("Test2: %d\n", r);

    return 0;
}

int maximumJumps(int *nums, int numsSize, int target)
{
    int d[1000] = {0}, x;
    for (int i = numsSize - 2; i >= 0; i--)
    {
        x = -1;
        for (int j = i + 1; j < numsSize; j++)
        {
            int g = nums[j] - nums[i];
            if (g < 0)
                g = -g;
            if (g <= target && d[j] >= 0)
            {
                int t = d[j];
                x = t > x ? t : x;
            }
        }
        d[i] = x == -1 ? -1 : x + 1;
    }
    return d[0] == -1 ? -1 : d[0];
}