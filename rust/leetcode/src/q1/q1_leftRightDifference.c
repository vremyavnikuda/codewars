/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int *leftRightDifference(int *nums, int numsSize, int *returnSize)
{
    int *a, *b, *c, *d, *e, f = 0, g = 0, h;
    *returnSize = numsSize;
    if (!numsSize || !(a = (int *)malloc(numsSize * sizeof(int))))
        return 0;
    for (e = (d = nums) + numsSize; d < e; g += *d++)
        ;
    for (b = a, c = a + numsSize, d = nums; b < c; *b++ = (h = f - g) < 0 ? -h : h, f += *d++)
        g -= *d;
    return a;
}
