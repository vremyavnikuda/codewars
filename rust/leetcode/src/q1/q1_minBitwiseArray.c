/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
#include <stdlib.h>
int* minBitwiseArray(int* nums, int numsSize, int* returnSize) {
    *returnSize = numsSize;
    int* ans = (int*)malloc(numsSize * sizeof(int));
    
    for (int j = 0; j < numsSize; ++j) {
        int x = nums[j];
        
        if (x == 2) {
            ans[j] = -1;
        } else {
            // Find first 0 bit from right (after skipping trailing 1s)
            // Optimized: use __builtin_ctz to find trailing ones faster
            int pos = __builtin_ctz(~x);
            ans[j] = x ^ (1 << (pos - 1));
        }
    }
    
    return ans;
}
