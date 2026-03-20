/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume
 * caller calls free().
 */
#include <limits.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

static inline void _s(int *a, int n) {
  int l[64], r[64], t = 0;
  if (n < 2)
    return;
  l[0] = 0, r[0] = n - 1;
  while (t >= 0) {
    int i0 = l[t], j0 = r[t--];
    while (j0 - i0 > 22) {
      int i = i0, j = j0, p = a[(i0 + j0) >> 1];
      do {
        while (a[i] < p)
          ++i;
        while (a[j] > p)
          --j;
        if (i <= j) {
          int x = a[i];
          a[i++] = a[j];
          a[j--] = x;
        }
      } while (i <= j);
      if (j - i0 < j0 - i) {
        if (i < j0)
          l[++t] = i, r[t] = j0;
        j0 = j;
      } else {
        if (i0 < j)
          l[++t] = i0, r[t] = j;
        i0 = i;
      }
    }
    for (int i = i0 + 1; i <= j0; ++i) {
      int v = a[i], j = i - 1;
      while (j >= i0 && a[j] > v)
        a[j + 1] = a[j], --j;
      a[j + 1] = v;
    }
  }
}

int **minAbsDiff(int **grid, int gridSize, int *gridColSize, int k,
                 int *returnSize, int **returnColumnSizes) {
  enum { W = 4096 };
  static unsigned m[W + 1];
  static unsigned z = 1;

  int a = gridSize;
  int b = (grid && gridColSize && a > 0) ? gridColSize[0] : 0;
  int p = (k > 0 && a >= k) ? (a - k + 1) : 0;
  int q = (k > 0 && b >= k) ? (b - k + 1) : 0;

  int **o = 0;
  int *d = 0, *u = 0, *c = 0;

  if (returnSize)
    *returnSize = p;
  if (!returnColumnSizes)
    return 0;
  *returnColumnSizes = 0;
  if (p <= 0 || q <= 0)
    return 0;

  o = (int **)malloc((size_t)p * sizeof(*o));
  d = (int *)malloc((size_t)p * (size_t)q * sizeof(*d));
  u = (int *)malloc((size_t)k * (size_t)k * sizeof(*u));
  c = (int *)malloc((size_t)p * sizeof(*c));
  if (!o || !d || !u || !c) {
    free(c), free(u), free(d), free(o);
    if (returnSize)
      *returnSize = 0;
    return 0;
  }

  for (int i = 0; i < p; ++i)
    o[i] = d + (size_t)i * (size_t)q, c[i] = q;
  *returnColumnSizes = c;

  for (int i = 0; i < p; ++i) {
    for (int j = 0; j < q; ++j) {
      int t = 0, lo = INT_MAX, hi = INT_MIN;

      for (int x = i; x < i + k; ++x) {
        int *g = grid[x] + j;
        for (int y = 0; y < k; ++y) {
          int v = g[y];
          u[t++] = v;
          lo = v < lo ? v : lo;
          hi = v > hi ? v : hi;
        }
      }

      if (lo == hi) {
        o[i][j] = 0;
        continue;
      }

      {
        int ans = INT_MAX;
        int64_t s = (int64_t)hi - (int64_t)lo;

        if (s >= 0 && s <= W) {
          int prev = -1;
          if (++z == 0) {
            memset(m, 0, sizeof(m));
            z = 1;
          }
          for (int x = 0; x < t; ++x)
            m[u[x] - lo] = z;

          for (int x = 0; x <= (int)s; ++x) {
            if (m[x] == z) {
              if (prev >= 0) {
                int w = x - prev;
                ans = w < ans ? w : ans;
                if (ans == 1)
                  break;
              }
              prev = x;
            }
          }
        } else {
          _s(u, t);
          {
            int prev = u[0];
            for (int x = 1; x < t; ++x) {
              int v = u[x];
              if (v != prev) {
                int64_t w64 = (int64_t)v - (int64_t)prev;
                int w = (w64 > (int64_t)INT_MAX) ? INT_MAX : (int)w64;
                ans = w < ans ? w : ans;
                prev = v;
                if (ans == 1)
                  break;
              }
            }
          }
        }

        o[i][j] = (ans == INT_MAX) ? 0 : ans;
      }
    }
  }

  free(u);
  return o;
}
