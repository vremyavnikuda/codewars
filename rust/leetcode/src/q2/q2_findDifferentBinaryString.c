#include <stdlib.h>

char* findDifferentBinaryString(char** nums, int numsSize) {
  char *r = (char *)malloc((size_t)numsSize + 1u), **p = nums, *q = r;
  int i = 0;
  for (; i < numsSize; ++i) q[i] = (char)(97 - p[i][i]);
  q[i] = 0;
  return r;
}
