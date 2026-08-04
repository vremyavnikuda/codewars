#include <stdlib.h>

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* findMissingElements(int* nums, int numsSize, int* returnSize) {
    int q1 = 100, q2 = 0;
    for (int q3 = 0; q3 < numsSize; ++q3) {
        if (nums[q3] < q1) q1 = nums[q3];
        if (nums[q3] > q2) q2 = nums[q3];
    }
    int q4 = q2 - q1 - 1;
    if (q4 < 0) q4 = 0;
    int* q5 = (int*)malloc(q4 * sizeof(int));
    unsigned char* q6 = (unsigned char*)calloc((size_t)(q2 - q1 + 1), 1);
    for (int q7 = 0; q7 < numsSize; ++q7) q6[nums[q7] - q1] = 1;
    int q8 = 0;
    for (int q9 = q1 + 1; q9 < q2; ++q9)
        if (!q6[q9 - q1]) q5[q8++] = q9;
    free(q6);
    *returnSize = q8;
    return q5;
}
