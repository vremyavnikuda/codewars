int maxDotProduct(int *nums1, int nums1Size, int *nums2, int nums2Size) {
  int *a = nums1, *b = nums2, m = nums1Size, n = nums2Size;
  if (m < n) {
    int *t = a;
    a = b;
    b = t;
    int x = m;
    m = n;
    n = x;
  }
  int f[n + 1], i, j, v, p, pr;
  for (j = 0; j <= n; ++j)
    f[j] = -0x3f3f3f3f;
  for (i = 0; i < m; ++i) {
    pr = -0x3f3f3f3f;
    for (j = 0; j < n; ++j) {
      v = a[i] * b[j];
      p = pr > 0 ? pr + v : v;
      pr = f[j + 1];
      if (f[j] > f[j + 1])
        f[j + 1] = f[j];
      if (p > f[j + 1])
        f[j + 1] = p;
    }
  }
  return f[n];
}
