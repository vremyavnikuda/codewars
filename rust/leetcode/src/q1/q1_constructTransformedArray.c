/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
#include <stdlib.h>
int *constructTransformedArray(int *nums, int numsSize, int *returnSize) {
  int n = numsSize;
  *returnSize = n;
  if (n <= 0) return NULL;
  int *a = (int *)malloc((size_t)n * sizeof(int));
  if (!a) return NULL;
  for (int i = 0; i < n; ++i) {
    int t = nums[i] % n;
    t += (t < 0) ? n : 0;
    int j = i + t;
    j -= (j >= n) ? n : 0;
    a[i] = nums[j];
  }
  return a;
}
