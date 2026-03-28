#include <stdlib.h>
#include <string.h>

static char *Z(void) {
  char *p = (char *)malloc(1);
  if (p)
    *p = 0;
  return p;
}

char *findTheString(int **lcp, int lcpSize, int *lcpColSize) {
  int n = lcpSize, i = 0, j, k;
  char *s;
  (void)lcpColSize;
  s = (char *)malloc((size_t)n + 1);
  if (!s)
    return 0;
  memset(s, 0, (size_t)n), s[n] = 0;
#define R        \
  do {           \
    free(s);     \
    return Z();  \
  } while (0)
  for (k = 0; k < 26; ++k) {
    while (i < n && s[i])
      ++i;
    if (i == n)
      break;
    for (j = i; j < n; ++j)
      if (lcp[i][j])
        s[j] = (char)('a' + k);
  }
  for (i = 0; i < n; ++i)
    if (!s[i])
      R;
  for (i = n; i--;) {
    for (j = n; j--;) {
      if (s[i] == s[j]) {
        if (lcp[i][j] != ((i == n - 1 || j == n - 1) ? 1 : lcp[i + 1][j + 1] + 1))
          R;
      } else if (lcp[i][j]) {
        R;
      }
    }
  }
#undef R
  return s;
}
