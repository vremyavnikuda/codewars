int minimumDeleteSum(char *s1, char *s2) {
  int m = 0, n = 0, i, j, pr, t;
  while (s1[m])
    m++;
  while (s2[n])
    n++;
  char *a = s1, *b = s2;
  if (m < n) {
    char *x = a;
    a = b;
    b = x;
    int y = m;
    m = n;
    n = y;
  }
  int f[n + 1];
  f[0] = 0;
  for (j = 1; j <= n; ++j)
    f[j] = f[j - 1] + b[j - 1];
  for (i = 1; i <= m; ++i) {
    pr = f[0];
    f[0] += a[i - 1];
    for (j = 1; j <= n; ++j) {
      t = f[j];
      if (a[i - 1] == b[j - 1])
        f[j] = pr;
      else {
        int x = f[j] + a[i - 1];
        int y = f[j - 1] + b[j - 1];
        f[j] = x < y ? x : y;
      }
      pr = t;
    }
  }
  return f[n];
}
