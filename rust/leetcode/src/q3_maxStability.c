#include <stdlib.h>

typedef struct {
  int *p, *w, c;
} Z;

static inline void _(Z *z, int n) {
  int i = 0;
  z->c = n;
  for (; i < n; ++i)
    z->p[i] = i, z->w[i] = 1;
}

static inline int __ (Z *z, int x) {
  int *p = z->p;
  while (p[x] != x)
    p[x] = p[p[x]], x = p[x];
  return x;
}

static inline int ___(Z *z, int a, int b) {
  int x = __(z, a), y = __(z, b), t;
  if (x == y)
    return 0;
  if (z->w[x] < z->w[y])
    t = x, x = y, y = t;
  z->p[y] = x;
  z->w[x] += z->w[y];
  --z->c;
  return 1;
}

static inline int ____(
  int n, int **edges, int edgesSize, int k, int lim, Z *z
) {
  int i = 0, r = k;
  _(z, n);
  for (; i < edgesSize; ++i) {
    int *e = edges[i];
    if (e[2] >= lim)
      ___(z, e[0], e[1]);
  }
  for (i = 0; i < edgesSize && r; ++i) {
    int *e = edges[i];
    if (e[2] >= ((lim + 1) >> 1) && ___(z, e[0], e[1]))
      --r;
  }
  return z->c == 1;
}

int maxStability(int n, int **edges, int edgesSize, int *edgesColSize, int k) {
  int i = 0, l = 1, r = 1000000;
  int *buf;
  Z z;
  (void)edgesColSize;

  if (n <= 0)
    return -1;

  buf = (int *)malloc((size_t)n * 2u * sizeof(int));
  if (!buf)
    return -1;

  z.p = buf;
  z.w = buf + n;
  _( &z, n);

  for (; i < edgesSize; ++i) {
    int *e = edges[i];
    if (e[3]) {
      if (e[2] < r)
        r = e[2];
      if (!___(&z, e[0], e[1])) {
        free(buf);
        return -1;
      }
    }
  }

  for (i = 0; i < edgesSize; ++i) {
    int *e = edges[i];
    ___(&z, e[0], e[1]);
  }
  if (z.c > 1) {
    free(buf);
    return -1;
  }

  while (l < r) {
    int m = (l + r + 1) >> 1;
    if (____(n, edges, edgesSize, k, m, &z))
      l = m;
    else
      r = m - 1;
  }

  free(buf);
  return l;
}
