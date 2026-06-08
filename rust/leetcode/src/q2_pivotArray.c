#include <stdlib.h>

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int *pivotArray(int *nums, int numsSize, int pivot, int *returnSize)
{
    int *a = (int *)malloc((*returnSize = numsSize) * sizeof(int));
    int b = 0, c = 0;
    for (int *d = nums; d - nums < numsSize; ++d)
        b += *d<pivot, c += *d> pivot;
    int *e[] = {a, a + b, a + numsSize - c};
    for (int *d = nums; d - nums < numsSize; ++d)
        *e[*d < pivot ? 0 : *d > pivot ? 2
                                       : 1]++ = *d;
    return a;
}