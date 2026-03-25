#include <limits.h>
#include <stdlib.h>

#define D0(i, j) d0[(i) * w + (j)]
#define D1(i, j) d1[(i) * w + (j)]
#define H(v)                                                                  \
    do {                                                                      \
        int _ = (v);                                                          \
        if ((_ ^ a) && (_ ^ b) && (_ ^ c)) {                                  \
            if (_ > a) {                                                      \
                c = b;                                                        \
                b = a;                                                        \
                a = _;                                                        \
            } else if (_ > b) {                                               \
                c = b;                                                        \
                b = _;                                                        \
            } else if (_ > c) {                                               \
                c = _;                                                        \
            }                                                                 \
        }                                                                     \
    } while (0)

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* getBiggestThree(int** grid, int gridSize, int* gridColSize, int* returnSize) {
    int m = gridSize, n = gridColSize[0], w = n + 2, z = (m + 1) * w;
    int *r = (int *)malloc(3U * sizeof(int));
    int *u = (int *)calloc((size_t)z << 1, sizeof(int));
    int a = INT_MIN, b = INT_MIN, c = INT_MIN;
    if (!r) {
        *returnSize = 0;
        free(u);
        return NULL;
    }
    if (!u) {
        free(r);
        *returnSize = 0;
        return NULL;
    }
    int *d0 = u, *d1 = u + z;
    for (int i = 1; i <= m; ++i) {
        int *g = grid[i - 1];
        int p = i * w, q = p - w;
        for (int j = 1; j <= n; ++j) {
            D0(i, j) = d0[q + j - 1] + g[j - 1];
            D1(i, j) = d1[q + j + 1] + g[j - 1];
        }
    }
    for (int i = 1; i <= m; ++i) {
        int *g = grid[i - 1];
        for (int j = 1; j <= n; ++j) {
            int l = i - 1;
            H(g[j - 1]);
            if (m - i < l) l = m - i;
            if (j - 1 < l) l = j - 1;
            if (n - j < l) l = n - j;
            for (int k = 1; k <= l; ++k) {
                H((D0(i + k, j) - D0(i, j - k)) + (D0(i, j + k) - D0(i - k, j)) +
                  (D1(i, j - k) - D1(i - k, j)) + (D1(i + k, j) - D1(i, j + k)) -
                  grid[i + k - 1][j - 1] + grid[i - k - 1][j - 1]);
            }
        }
    }
    free(u);
    *returnSize = 1 + (b != INT_MIN) + (c != INT_MIN);
    r[0] = a;
    if (*returnSize > 1) r[1] = b;
    if (*returnSize > 2) r[2] = c;
    return r;
}
