#include <stdio.h>

int countNegatives(int **grid, int gridSize, int *gridColSize) {
  int m = gridSize;
  int n = gridColSize[0];
  int i = m - 1;
  int j = 0;
  int a = 0;
  while (i >= 0 && j < n) {
    if (grid[i][j] >= 0) {
      j++;
    } else {
      a += n - j;
      i--;
    }
  }
  return a;
}

int main() {
  int r1[] = {4, 3, 2, -1};
  int r2[] = {3, 2, 1, -1};
  int r3[] = {1, 1, -1, -2};
  int r4[] = {-1, -1, -2, -3};
  int *g1[] = {r1, r2, r3, r4};
  int c1[] = {4, 4, 4, 4};

  int r5[] = {3, 2};
  int r6[] = {1, 0};
  int *g2[] = {r5, r6};
  int c2[] = {2, 2};

  printf("%d\n", countNegatives(g1, 4, c1));
  printf("%d\n", countNegatives(g2, 2, c2));

  return 0;
}