#include <stdio.h>
#include <stdlib.h>

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int *plusOne(int *digits, int digitsSize, int *returnSize) {
  int c = 1;
  for (int i = digitsSize - 1; i >= 0 && c; --i) {
    c = (digits[i] += c) / 10;
    digits[i] %= 10;
  }
  if (c) {
    *returnSize = digitsSize + 1;
    int *r = (int *)malloc(*returnSize * sizeof(int));
    r[0] = 1;
    for (int i = 1; i <= digitsSize; ++i) {
      r[i] = digits[i - 1];
    }
    return r;
  }
  *returnSize = digitsSize;
  int *r = (int *)malloc(*returnSize * sizeof(int));
  for (int i = 0; i < digitsSize; ++i) {
    r[i] = digits[i];
  }
  return r;
}

int main() {
  int d1[] = {1, 2, 3};
  int d2[] = {9, 9, 9};
  int d3[] = {4, 3, 2, 1};

  int s1, s2, s3;
  int *r1 = plusOne(d1, 3, &s1);
  int *r2 = plusOne(d2, 3, &s2);
  int *r3 = plusOne(d3, 4, &s3);

  printf("Test 1: ");
  for (int i = 0; i < s1; ++i)
    printf("%d ", r1[i]);
  printf("\n");

  printf("Test 2: ");
  for (int i = 0; i < s2; ++i)
    printf("%d ", r2[i]);
  printf("\n");

  printf("Test 3: ");
  for (int i = 0; i < s3; ++i)
    printf("%d ", r3[i]);
  printf("\n");

  free(r1);
  free(r2);
  free(r3);

  return 0;
}
