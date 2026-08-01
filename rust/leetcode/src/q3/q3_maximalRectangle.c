int lra(int *h, int n) {
  int stk[n], l[n], r[n], i, t = 0, res = 0;
  for (i = 0; i < n; ++i)
    l[i] = -1, r[i] = n;
  for (i = 0; i < n; ++i) {
    while (t && h[stk[t - 1]] >= h[i])
      r[stk[--t]] = i;
    if (t)
      l[i] = stk[t - 1];
    stk[t++] = i;
  }
  for (i = 0; i < n; ++i) {
    int a = h[i] * (r[i] - l[i] - 1);
    if (a > res)
      res = a;
  }
  return res;
}

int maximalRectangle(char **matrix, int matrixSize, int *matrixColSize) {
  int m = matrixSize, n = *matrixColSize, i, j, ans = 0;
  int h[n];
  for (j = 0; j < n; ++j)
    h[j] = 0;
  for (i = 0; i < m; ++i) {
    for (j = 0; j < n; ++j)
      h[j] = matrix[i][j] == '1' ? h[j] + 1 : 0;
    int t = lra(h, n);
    if (t > ans)
      ans = t;
  }
  return ans;
}
