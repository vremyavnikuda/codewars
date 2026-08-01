#include <stdint.h>
#include <stdlib.h>
#include <string.h>

int numberOfSubmatrices(char** grid, int gridSize, int* gridColSize) {
  int z = 0, m = gridSize, n, i = 0;
  static uint64_t s[1001];
  static const uint64_t d[256] = {[88] = 0x100000000ULL, [89] = 0x1ULL};
  if (!(grid && gridColSize && m > 0 && (n = gridColSize[0]) > 0))
    return 0;
  {
    uint64_t *x, *v = 0;
    if (n <= 1000) {
      x = s + 1;
      memset(s, 0, ((size_t)n + 1) * sizeof(*s));
    } else {
      v = (uint64_t *)calloc((size_t)n + 1, sizeof(*v));
      if (!v)
        return 0;
      x = v + 1;
    }
    while (i < m) {
      unsigned char *r = (unsigned char *)grid[i];
      uint64_t p = 0;
      int j = 0;
      while (j + 3 < n) {
        uint64_t w;
        unsigned a, b;
        w = (x[j] += (p += d[r[j]])), a = (unsigned)(w >> 32), b = (unsigned)w,
        z += ((a != 0U) & (a == b)), ++j;
        w = (x[j] += (p += d[r[j]])), a = (unsigned)(w >> 32), b = (unsigned)w,
        z += ((a != 0U) & (a == b)), ++j;
        w = (x[j] += (p += d[r[j]])), a = (unsigned)(w >> 32), b = (unsigned)w,
        z += ((a != 0U) & (a == b)), ++j;
        w = (x[j] += (p += d[r[j]])), a = (unsigned)(w >> 32), b = (unsigned)w,
        z += ((a != 0U) & (a == b)), ++j;
      }
      while (j < n) {
        uint64_t v = (x[j] += (p += d[r[j]]));
        unsigned a = (unsigned)(v >> 32), b = (unsigned)v;
        z += ((a != 0U) & (a == b)), ++j;
      }
      ++i;
    }
    free(v);
  }
  return z;
}
