#include <limits.h>
#include <stdlib.h>

#define M(a, b) ((a) > (b) ? (a) : (b))

int maximumAmount(int** coins, int coinsSize, int* coinsColSize) {
  int a = coinsSize, b = (a > 0) ? coinsColSize[0] : 0;
  if (!(coins && coinsColSize && a > 0 && b > 0)) return 0;
  enum { K = 3 };
  const int z = INT_MIN / 4;
  int* d = (int*)malloc((size_t)b * K * sizeof(int));
  if (!d) return 0;
  for (int i = 0, n = b * K; i < n; ++i) d[i] = z;
  for (int i = a - 1; i >= 0; --i) {
    int* r = coins[i];
    for (int j = b - 1; j >= 0; --j) {
      int o = j * K, x = r[j];
      if ((i == a - 1) & (j == b - 1)) {
        int y = x < 0 ? 0 : x;
        d[o] = x;
        d[o + 1] = y;
        d[o + 2] = y;
      } else {
        int d0 = d[o], d1 = d[o + 1], d2 = d[o + 2];
        int r0 = (j + 1 < b) ? d[o + 3] : z;
        int r1 = (j + 1 < b) ? d[o + 4] : z;
        int r2 = (j + 1 < b) ? d[o + 5] : z;
        int n0 = x + M(d0, r0);
        int n1 = x + M(d1, r1);
        int n2 = x + M(d2, r2);
        if (x < 0) {
          int t1 = M(d0, r0), t2 = M(d1, r1);
          n1 = M(n1, t1);
          n2 = M(n2, t2);
        }
        d[o] = n0;
        d[o + 1] = n1;
        d[o + 2] = n2;
      }
    }
  }
  a = d[2];
  free(d);
  return a;
}

#undef M
