#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#define M 27
#define MOD 1000000007

bool f1(int x) {
  int l = -1;
  for (int i = 0; i < 3; ++i) {
    if (x % 3 == l)
      return false;
    l = x % 3;
    x /= 3;
  }
  return true;
}

bool f2(int x, int y) {
  for (int i = 0; i < 3; ++i) {
    if (x % 3 == y % 3)
      return false;
    x /= 3;
    y /= 3;
  }
  return true;
}

int numOfWays(int n) {
  int v[M], vc = 0, f[M], d[M][M], dc[M];
  memset(f, 0, sizeof(f));
  memset(dc, 0, sizeof(dc));
  for (int i = 0; i < M; ++i) {
    if (f1(i)) {
      v[vc++] = i;
      f[i] = 1;
    }
  }
  for (int i = 0; i < vc; ++i) {
    for (int j = 0; j < vc; ++j) {
      if (f2(v[i], v[j])) {
        d[v[i]][dc[v[i]]++] = v[j];
      }
    }
  }
  for (int k = 1; k < n; ++k) {
    int g[M];
    memset(g, 0, sizeof(g));
    for (int i = 0; i < vc; ++i) {
      int vi = v[i];
      for (int j = 0; j < dc[vi]; ++j) {
        int vj = d[vi][j];
        g[vj] = (g[vj] + f[vi]) % MOD;
      }
    }
    memcpy(f, g, sizeof(f));
  }
  int a = 0;
  for (int i = 0; i < M; ++i) {
    a = (a + f[i]) % MOD;
  }
  return a;
}

int main() {
  printf("%d\n", numOfWays(1));
  printf("%d\n", numOfWays(2));
  printf("%d\n", numOfWays(3));
  printf("%d\n", numOfWays(7));
  return 0;
}
