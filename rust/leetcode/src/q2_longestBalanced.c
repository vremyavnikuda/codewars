#include <stdlib.h>
#include <string.h>

static int q2lb_c(const void *a, const void *b) {
  int x = *(const int *)a;
  int y = *(const int *)b;
  return (x > y) - (x < y);
}

int longestBalanced(int *nums, int numsSize) {
  int n = numsSize;
  if (n <= 1) return 0;
  int *t = (int *)malloc((size_t)n * sizeof(int));
  if (!t) return 0;
  memcpy(t, nums, (size_t)n * sizeof(int));
  qsort(t, (size_t)n, sizeof(int), q2lb_c);
  int m = 0;
  for (int i = 0; i < n; ++i) {
    if (i == 0 || t[i] != t[i - 1]) t[m++] = t[i];
  }
  int *u = (int *)malloc((size_t)n * sizeof(int));
  if (!u) {
    free(t);
    return 0;
  }
  unsigned char *p = (unsigned char *)malloc((size_t)m);
  if (!p) {
    free(u);
    free(t);
    return 0;
  }
  for (int i = 0; i < m; ++i) p[i] = (unsigned char)(t[i] & 1);
  for (int i = 0; i < n; ++i) {
    int x = nums[i];
    int l = 0, r = m - 1;
    while (l <= r) {
      int d = (l + r) >> 1;
      int v = t[d];
      if (v == x) {
        u[i] = d;
        break;
      }
      if (v < x) {
        l = d + 1;
      } else {
        r = d - 1;
      }
    }
  }
  int *s = (int *)calloc((size_t)m, sizeof(int));
  if (!s) {
    free(p);
    free(u);
    free(t);
    return 0;
  }
  int a = 0;
  for (int i = 0; i < n; ++i) {
    if (n - i <= a) break;
    int b = 0, c = 0;
    int z = i + 1;
    for (int j = i; j < n; ++j) {
      int k = u[j];
      if (s[k] != z) {
        s[k] = z;
        if (p[k])
          ++c;
        else
          ++b;
      }
      if (b == c) {
        int len = j - i + 1;
        if (len > a) a = len;
      }
    }
  }
  free(s);
  free(p);
  free(u);
  free(t);
  return a;
}
