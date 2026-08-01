int countSubmatrices(int **grid, int gridSize, int *gridColSize, int k) {
#define Q(x) ((x) <= k)
  int a = 0, b = gridSize, c;
  if (!(grid && gridColSize && b > 0 && (c = gridColSize[0]) > 0))
    return 0;
  {
    int *r = grid[0], j = 0, p = 0;
    while (j < c) {
      r[j] = (p += r[j]);
      a += Q(r[j]);
      ++j;
    }
  }
  for (int i = 1; i < b; ++i) {
    int *x = grid[i], *y = grid[i - 1], j = 0, l = 0, u = 0;
    while (j < c) {
      int t = y[j], v = x[j] + t + l - u;
      u = t;
      l = v;
      x[j] = v;
      a += Q(v);
      ++j;
    }
  }
#undef Q
  return a;
}
