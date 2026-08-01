/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
#include <stdlib.h>
int* minBitwiseArray(int* nums, int numsSize, int* returnSize) {
    *returnSize = numsSize;
    int* ans = (int*)malloc(numsSize * sizeof(int));
    
    for (int j = 0; j < numsSize; j++) {
        int x = nums[j];
        if (x == 2) {
            ans[j] = -1;
        } else {
            for (int i = 1; i < 32; i++) {
                if (((x >> i) & 1) ^ 1) {
                    ans[j] = x ^ (1 << (i - 1));
                    break;
                }
            }
        }
    }
    
    return ans;
}