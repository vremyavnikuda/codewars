/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume
 * caller calls free().
 */
#include <stdlib.h>
#include <string.h>

char **rotateTheBox(char **boxGrid, int boxGridSize, int *boxGridColSize,
                    int *returnSize, int **returnColumnSizes) {
  int a = boxGridSize, b = (boxGridColSize && a > 0) ? *boxGridColSize : 0, i,
      j, k;
  char **r;

  *returnSize = b;
  *returnColumnSizes =
      b ? (int *)malloc((size_t)b * sizeof(**returnColumnSizes)) : 0;
  r = b ? (char **)malloc((size_t)b * sizeof(*r)) : 0;
  if (b && (!r || !*returnColumnSizes)) {
    free(r), free(*returnColumnSizes), *returnColumnSizes = 0, *returnSize = 0;
    return 0;
  }
  for (i = 0; i < b; ++i) {
    (*returnColumnSizes)[i] = a;
    r[i] = (char *)malloc((size_t)a);
    if (!r[i]) {
      while (i)
        free(r[--i]);
      free(r), free(*returnColumnSizes), *returnColumnSizes = 0,
                                         *returnSize = 0;
      return 0;
    }
    memset(r[i], '.', (size_t)a);
  }
  for (i = 0; i < a; ++i)
    for (k = b, j = b - 1; ~j; --j)
      boxGrid[i][j] == '*'   ? (r[j][a - 1 - i] = '*', k = j)
      : boxGrid[i][j] == '#' ? (r[--k][a - 1 - i] = '#', 0)
                             : 0;
  return r;
}
