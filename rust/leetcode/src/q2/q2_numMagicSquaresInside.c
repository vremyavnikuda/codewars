#include <stdio.h>

int check(int **grid, int m, int n, int i, int j) {
  if (i + 3 > m || j + 3 > n) {
    return 0;
  }

  int cnt[16] = {0};
  int row[3] = {0};
  int col[3] = {0};
  int a = 0, b = 0;

  for (int x = i; x < i + 3; ++x) {
    for (int y = j; y < j + 3; ++y) {
      int v = grid[x][y];
      if (v < 1 || v > 9 || ++cnt[v] > 1) {
        return 0;
      }
      row[x - i] += v;
      col[y - j] += v;
      if (x - i == y - j) {
        a += v;
      }
      if (x - i + y - j == 2) {
        b += v;
      }
    }
  }

  if (a != b) {
    return 0;
  }

  for (int k = 0; k < 3; ++k) {
    if (row[k] != a || col[k] != a) {
      return 0;
    }
  }

  return 1;
}

int numMagicSquaresInside(int **grid, int gridSize, int *gridColSize) {
  int m = gridSize;
  int n = gridColSize[0];
  int ans = 0;

  for (int i = 0; i < m; ++i) {
    for (int j = 0; j < n; ++j) {
      ans += check(grid, m, n, i, j);
    }
  }

  return ans;
}

int main() {
  int r1[] = {4, 3, 8, 4};
  int r2[] = {9, 5, 1, 9};
  int r3[] = {2, 7, 6, 2};
  int *g1[] = {r1, r2, r3};
  int c1[] = {4, 4, 4};

  int r4[] = {8};
  int *g2[] = {r4};
  int c2[] = {1};

  int r5[] = {4, 3, 8};
  int r6[] = {9, 5, 1};
  int r7[] = {2, 7, 6};
  int *g3[] = {r5, r6, r7};
  int c3[] = {3, 3, 3};

  printf("Test 1: %d\n", numMagicSquaresInside(g1, 3, c1));
  printf("Test 2: %d\n", numMagicSquaresInside(g2, 1, c2));
  printf("Test 3: %d\n", numMagicSquaresInside(g3, 3, c3));

  return 0;
}
