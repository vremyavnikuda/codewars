/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
#include <stdlib.h>

#define A(u, v) ((u) < (v) ? (v) : (u))
#define B(u, v) ((u) < (v) ? (u) : (v))

int *maxValue(int *nums, int numsSize, int *returnSize) {
  int *r, *p, *q, *e, x, y, z;
  if (returnSize)
    *returnSize = numsSize;
  if (numsSize < 1)
    return NULL;
  r = (int *)malloc((size_t)numsSize * sizeof(int));
  if (!r) {
    if (returnSize)
      *returnSize = 0;
    return NULL;
  }
  *r = x = *nums;
  for (p = nums + 1, q = r + 1, e = r + numsSize; q < e; ++p, ++q)
    *q = x = A(x, *p);
  for (p = nums + numsSize, q = r + numsSize, x = 0x7fffffff, y = 0; q != r;
       x = B(x, *p)) {
    --p;
    --q;
    z = *q;
    *q = z > x ? y : (y = z);
  }
  return r;
}
