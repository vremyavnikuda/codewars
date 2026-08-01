#include <stdlib.h>
int maxSideLength(int** mat, int matSize, int* matColSize, int threshold) {
    int m = matSize;
    if (m == 0) {
        return 0;
    }
    int n = matColSize[0];

    int rows = m + 1;
    int cols = n + 1;
    int total = rows * cols;
    int* s = (int*)calloc((size_t)total, sizeof(int));
    if (!s) {
        return 0;
    }

    for (int i = 1; i <= m; ++i) {
        int row_base = i * cols;
        int prev_base = (i - 1) * cols;
        for (int j = 1; j <= n; ++j) {
            s[row_base + j] = s[prev_base + j] + s[row_base + j - 1]
                              - s[prev_base + j - 1] + mat[i - 1][j - 1];
        }
    }

    int left = 0;
    int right = (m < n) ? m : n;
    while (left < right) {
        int mid = (left + right + 1) >> 1;
        int ok = 0;
        if (mid == 0) {
            ok = 1;
        } else {
            int limit_i = m - mid;
            int limit_j = n - mid;
            for (int i = 0; i <= limit_i && !ok; ++i) {
                int i0 = i * cols;
                int i1 = (i + mid) * cols;
                for (int j = 0; j <= limit_j; ++j) {
                    int sum = s[i1 + j + mid] - s[i0 + j + mid]
                              - s[i1 + j] + s[i0 + j];
                    if (sum <= threshold) {
                        ok = 1;
                        break;
                    }
                }
            }
        }

        if (ok) {
            left = mid;
        } else {
            right = mid - 1;
        }
    }

    free(s);
    return left;
}
