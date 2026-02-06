#include <stdlib.h>

static int f0(const void *p, const void *q) {
  int a = *(const int *)p;
  int b = *(const int *)q;
  return (a > b) - (a < b);
}

int minRemoval(int *nums, int numsSize, int k) {
  if (numsSize <= 1) return 0;
  qsort(nums, (size_t)numsSize, sizeof(int), f0);
  int a = numsSize;
  int b = a;
  int c = 0;
  for (int d = 0; d < a; ++d) {
    if (c < d) c = d;
    long long e = (long long)nums[d] * (long long)k;
    while (c < a && (long long)nums[c] <= e) {
      ++c;
    }
    int f = a - (c - d);
    if (f < b) b = f;
  }
  return b;
}
