#include <stdlib.h>

int cmp(const void *a, const void *b) {
  int *ea = *(int **)a;
  int *eb = *(int **)b;
  return ea[0] - eb[0];
}

int mx(int a, int b) { return a > b ? a : b; }

int maxTwoEvents(int **events, int eventsSize, int *eventsColSize) {
  qsort(events, eventsSize, sizeof(int *), cmp);

  int n = eventsSize;
  int *f = (int *)malloc((n + 1) * sizeof(int));
  f[n] = 0;

  for (int i = n - 1; i >= 0; --i) {
    f[i] = mx(f[i + 1], events[i][2]);
  }

  int ans = 0;

  for (int i = 0; i < n; ++i) {
    int v = events[i][2];
    int end = events[i][1];

    int l = 0, r = n;
    while (l < r) {
      int m = (l + r) >> 1;
      if (events[m][0] > end) {
        r = m;
      } else {
        l = m + 1;
      }
    }

    if (l < n) {
      v += f[l];
    }

    ans = mx(ans, v);
  }

  free(f);
  return ans;
}