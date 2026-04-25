#include <stdint.h>
#include <stdlib.h>

#define Z(a, b) (((uint64_t)(uint32_t)(a) << 32) | (uint32_t)(b))
#define U(a) ((int)((a) >> 32))
#define V(a) ((int)(a))

static int q3m(const void *a, const void *b) {
  uint64_t x = *(const uint64_t *)a, y = *(const uint64_t *)b;
  return (x > y) - (x < y);
}

static inline int q3d(uint64_t a, uint64_t b) {
  int x = U(a) - U(b), y = V(a) - V(b);
  return (x < 0 ? -x : x) + (y < 0 ? -y : y);
}

static int q3v(uint64_t *p, uint64_t *q, int n, int k, int d) {
  int h = 0, t = 1, i, s, l, m = 1, a, b;
  q[0] = 1;
  for (i = 1; i < n; ++i) {
    s = i, l = 1;
    while (h < t && q3d(p[i], p[h]) >= d) {
      a = (int)(q[h] >> 32), b = (int)q[h++];
      if (q3d(p[i], p[a]) >= d && b + 1 >= l) {
        s = a, l = b + 1;
        if ((m = m < l ? l : m) >= k)
          return 1;
      }
    }
    q[t++] = ((uint64_t)(uint32_t)s << 32) | (uint32_t)l;
  }
  return m >= k;
}

int maxDistance(int side, int **points, int pointsSize, int *pointsColSize, int k) {
  uint64_t S = (uint32_t)side, *p, *q, z, x, y;
  int i, l = 0, r = side, m;
  (void)pointsColSize;
  if (pointsSize < 2 || !(p = malloc((size_t)pointsSize * 2 * sizeof *p)))
    return 0;
  q = p + pointsSize;
  for (i = 0; i < pointsSize; ++i) {
    x = (uint32_t)points[i][0], y = (uint32_t)points[i][1];
    p[i] = !x && y ? y : y == S && x ? S + x : x == S && y < S ? 3 * S - y : 4 * S - x;
  }
  qsort(p, (size_t)pointsSize, sizeof *p, q3m);
  for (i = 0; i < pointsSize; ++i) {
    z = p[i];
    p[i] = z <= S ? Z(0, z) : z <= 2 * S ? Z(z - S, S) : z <= 3 * S ? Z(S, 3 * S - z) : Z(4 * S - z, 0);
  }
  while (l < r) {
    m = l + (r - l + 1) / 2;
    if (q3v(p, q, pointsSize, k, m))
      l = m;
    else
      r = m - 1;
  }
  free(p);
  return l;
}
