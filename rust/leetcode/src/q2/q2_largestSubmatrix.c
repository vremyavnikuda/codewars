#include <stdlib.h>

#define Z(a, b) (((a) > (b)) ? (a) : (b))
#define Y(a, b)                                                                \
  do {                                                                         \
    int __t = (a);                                                             \
    (a) = (b);                                                                 \
    (b) = __t;                                                                 \
  } while (0)

static void _q_(int *v, int n) {
  int l[96], r[96], t = 0;
  if (n < 2)
    return;
  l[0] = 0;
  r[0] = n - 1;
  while (t >= 0) {
    int L = l[t], R = r[t--];
    while (R - L > 15) {
      int i = L, j = R, p = v[(L + R) >> 1];
      do {
        while (v[i] > p)
          ++i;
        while (v[j] < p)
          --j;
        if (i <= j) {
          Y(v[i], v[j]);
          ++i;
          --j;
        }
      } while (i <= j);
      if (j - L < R - i) {
        if (i < R) {
          l[++t] = i;
          r[t] = R;
        }
        R = j;
      } else {
        if (L < j) {
          l[++t] = L;
          r[t] = j;
        }
        L = i;
      }
    }
    for (int i = L + 1; i <= R; ++i) {
      int x = v[i], k = i - 1;
      while (k >= L && v[k] < x) {
        v[k + 1] = v[k];
        --k;
      }
      v[k + 1] = x;
    }
  }
}

int largestSubmatrix(int **matrix, int matrixSize, int *matrixColSize) {
  int m = matrixSize, n = (m > 0) ? matrixColSize[0] : 0, a = 0;
  if (!m || !n)
    return 0;
  {
    int s = 0;
    for (int x = n; x; x >>= 1)
      ++s;
    if ((long long)m <= (long long)n * (long long)(s ? s : 1)) {
      int *c = (int *)calloc((size_t)m + 1U, sizeof(int));
      if (c) {
        for (int i = 0; i < m; ++i) {
          int *u = matrix[i], *d = i ? matrix[i - 1] : NULL, w = 0;
          for (int j = 0; j < n; ++j) {
            int h = u[j];
            if (h) {
              h += i ? d[j] : 0;
              u[j] = h;
              ++c[h];
            }
          }
          for (int h = i + 1; h; --h) {
            w += c[h];
            a = Z(a, h * w);
            c[h] = 0;
          }
        }
        free(c);
        return a;
      }
    }
  }
  for (int i = 1; i < m; ++i) {
    int *u = matrix[i], *d = matrix[i - 1];
    for (int j = 0; j < n; ++j)
      if (u[j])
        u[j] += d[j];
  }
  for (int i = 0; i < m; ++i) {
    int *q = matrix[i];
    _q_(q, n);
    for (int j = 0; j < n; ++j)
      a = Z(a, q[j] * (j + 1));
  }
  return a;
}
