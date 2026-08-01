#include <stdio.h>
#include <stdlib.h>

long long maxMatrixSum(int **matrix, int matrixSize, int *matrixColSize) {
  long long s = 0;
  int mi = 1 << 30, c = 0;
  for (int i = 0; i < matrixSize; ++i) {
    for (int j = 0; j < matrixColSize[i]; ++j) {
      int x = matrix[i][j];
      c += x < 0 ? 1 : 0;
      int y = abs(x);
      mi = mi < y ? mi : y;
      s += y;
    }
  }
  return c % 2 == 0 ? s : s - mi * 2;
}

int main() {
  int r1[] = {1, -1};
  int r2[] = {-1, 1};
  int *m1[] = {r1, r2};
  int c1[] = {2, 2};
  int r3[] = {1, 2, 3};
  int r4[] = {-1, -2, -3};
  int r5[] = {1, 2, 3};
  int *m2[] = {r3, r4, r5};
  int c2[] = {3, 3, 3};
  printf("%lld\n", maxMatrixSum(m1, 2, c1));
  printf("%lld\n", maxMatrixSum(m2, 3, c2));
  return 0;
}
