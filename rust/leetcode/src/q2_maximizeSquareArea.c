#include <stdlib.h>
#include <stdint.h>

static inline void swap_int(int *a, int *b) {
    int t = *a;
    *a = *b;
    *b = t;
}

static inline int median3_value(const int *a, int i, int j, int k) {
    int ai = a[i];
    int aj = a[j];
    int ak = a[k];
    if (ai < aj) {
        if (aj < ak) {
            return aj;
        }
        return (ai < ak) ? ak : ai;
    }
    if (ai < ak) {
        return ai;
    }
    return (aj < ak) ? ak : aj;
}

static void insertion_sort_range(int *a, int lo, int hi) {
    for (int i = lo + 1; i <= hi; ++i) {
        int key = a[i];
        int j = i - 1;
        while (j >= lo && a[j] > key) {
            a[j + 1] = a[j];
            --j;
        }
        a[j + 1] = key;
    }
}

static void sort_int(int *a, int n) {
    if (n < 2) {
        return;
    }
    int stack[64];
    int top = 0;
    stack[top++] = 0;
    stack[top++] = n - 1;
    while (top) {
        int hi = stack[--top];
        int lo = stack[--top];
        while (hi - lo > 16) {
            int mid = lo + ((hi - lo) >> 1);
            int pivot = median3_value(a, lo, mid, hi);
            int i = lo;
            int j = hi;
            while (i <= j) {
                while (a[i] < pivot) {
                    ++i;
                }
                while (a[j] > pivot) {
                    --j;
                }
                if (i <= j) {
                    swap_int(&a[i], &a[j]);
                    ++i;
                    --j;
                }
            }
            if (j - lo < hi - i) {
                if (i < hi) {
                    stack[top++] = i;
                    stack[top++] = hi;
                }
                hi = j;
            } else {
                if (lo < j) {
                    stack[top++] = lo;
                    stack[top++] = j;
                }
                lo = i;
            }
        }
        insertion_sort_range(a, lo, hi);
    }
}

static inline uint32_t hash_u32(uint32_t x) {
    x ^= x >> 16;
    x *= 0x7feb352dU;
    x ^= x >> 15;
    x *= 0x846ca68bU;
    x ^= x >> 16;
    return x;
}

static inline void hash_insert(int *table, size_t mask, int key) {
    size_t idx = (size_t)hash_u32((uint32_t)key) & mask;
    while (table[idx] != 0 && table[idx] != key) {
        idx = (idx + 1) & mask;
    }
    table[idx] = key;
}

static inline int hash_contains(const int *table, size_t mask, int key) {
    size_t idx = (size_t)hash_u32((uint32_t)key) & mask;
    while (1) {
        int cur = table[idx];
        if (cur == 0) {
            return 0;
        }
        if (cur == key) {
            return 1;
        }
        idx = (idx + 1) & mask;
    }
}

int maximizeSquareArea(int m, int n, int* hFences, int hFencesSize, int* vFences, int vFencesSize) {
    int hCount = hFencesSize + 2;
    int vCount = vFencesSize + 2;
    int *hPos = (int *)malloc((size_t)hCount * sizeof(int));
    int *vPos = (int *)malloc((size_t)vCount * sizeof(int));
    if (!hPos || !vPos) {
        free(hPos);
        free(vPos);
        return -1;
    }

    for (int i = 0; i < hFencesSize; ++i) {
        hPos[i] = hFences[i];
    }
    hPos[hFencesSize] = 1;
    hPos[hFencesSize + 1] = m;

    for (int i = 0; i < vFencesSize; ++i) {
        vPos[i] = vFences[i];
    }
    vPos[vFencesSize] = 1;
    vPos[vFencesSize + 1] = n;

    sort_int(hPos, hCount);
    sort_int(vPos, vCount);

    int *smallPos = hPos;
    int smallCount = hCount;
    int *largePos = vPos;
    int largeCount = vCount;
    if (smallCount > largeCount) {
        smallPos = vPos;
        smallCount = vCount;
        largePos = hPos;
        largeCount = hCount;
    }

    uint64_t diffCount = (uint64_t)smallCount * (uint64_t)(smallCount - 1) / 2U;
    uint64_t target = diffCount * 2U;
    if (target < 4U) {
        target = 4U;
    }
    if (target > (uint64_t)SIZE_MAX) {
        free(hPos);
        free(vPos);
        return -1;
    }

    size_t cap = 1;
    while ((uint64_t)cap < target) {
        cap <<= 1;
    }
    int *table = (int *)malloc(cap * sizeof(int));
    if (!table) {
        free(hPos);
        free(vPos);
        return -1;
    }
    for (size_t i = 0; i < cap; ++i) {
        table[i] = 0;
    }
    size_t mask = cap - 1;

    for (int i = 1; i < smallCount; ++i) {
        int pi = smallPos[i];
        for (int j = 0; j < i; ++j) {
            int diff = pi - smallPos[j];
            if (diff > 0) {
                hash_insert(table, mask, diff);
            }
        }
    }

    int best = 0;
    int minLarge = largePos[0];
    for (int i = largeCount - 1; i > 0; --i) {
        int pi = largePos[i];
        if (pi - minLarge <= best) {
            break;
        }
        for (int j = 0; j < i; ++j) {
            int diff = pi - largePos[j];
            if (diff <= best) {
                break;
            }
            if (hash_contains(table, mask, diff)) {
                best = diff;
                break;
            }
        }
    }

    free(table);
    free(hPos);
    free(vPos);

    if (best <= 0) {
        return -1;
    }
    const int mod = 1000000007;
    long long area = (long long)best * (long long)best;
    return (int)(area % mod);
}
