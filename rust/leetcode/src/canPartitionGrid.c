#include <stdlib.h>
typedef struct {
  long long v;
  int r, c;
} E;
static int O(const void *a, const void *b) {
  return (((E *)a)->v > ((E *)b)->v) - (((E *)a)->v < ((E *)b)->v);
}
static int F(E *e, int n, long long d, int v, int z) {
  int l = 0, h = n;
  while (l < h) {
    int m = l + h >> 1;
    e[m].v < d ? l = m + 1 : (h = m);
  }
  for (; l < n && e[l].v == d; l++) {
    int x = z >> 1 ? e[l].c : e[l].r;
    if (z & 1 ? x <= v : x > v)
      return 1;
  }
  return 0;
}
bool canPartitionGrid(int **grid, int gridSize, int *gridColSize) {
  int m = gridSize, n = *gridColSize, N = m * n, i, j, k;
  long long T = 0, s, d;
  E *e = malloc(N * sizeof *e);
  for (k = i = 0; i < m; i++)
    for (j = 0; j < n; j++)
      e[k++] = (E){grid[i][j], i, j}, T += grid[i][j];
  qsort(e, N, sizeof *e, O);
  for (s = 0, i = 0; i < m - 1; i++) {
    for (j = 0; j < n; j++)
      s += grid[i][j];
    if (s + s == T)
      return free(e), 1;
    d = s + s < T ? T - s - s : s + s - T;
    if (s + s < T ? (m - i > 2 && n > 1 && F(e, N, d, i, 0)) ||
                        i + 2 == m &&
                            (grid[m - 1][0] == d || grid[m - 1][n - 1] == d) ||
                        n < 2 && (grid[i + 1][0] == d || grid[m - 1][0] == d)
                  : (i && n > 1 && F(e, N, d, i, 1)) ||
                        !i && (grid[0][0] == d || grid[0][n - 1] == d) ||
                        n < 2 && (grid[0][0] == d || grid[i][0] == d))
      return free(e), 1;
  }
  for (s = 0, j = 0; j < n - 1; j++) {
    for (i = 0; i < m; i++)
      s += grid[i][j];
    if (s + s == T)
      return free(e), 1;
    d = s + s < T ? T - s - s : s + s - T;
    if (s + s < T ? (n - j > 2 && m > 1 && F(e, N, d, j, 2)) ||
                        j + 2 == n &&
                            (grid[0][n - 1] == d || grid[m - 1][n - 1] == d) ||
                        m < 2 && (grid[0][j + 1] == d || grid[0][n - 1] == d)
                  : (j && m > 1 && F(e, N, d, j, 3)) ||
                        !j && (grid[0][0] == d || grid[m - 1][0] == d) ||
                        m < 2 && (grid[0][0] == d || grid[0][j] == d))
      return free(e), 1;
  }
  return free(e), 0;
}
