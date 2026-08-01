static inline void swap_int(int* a, int* b) {
    int t = *a;
    *a = *b;
    *b = t;
}

static inline int median3_value(int* a, int i, int j, int k) {
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

static void insertion_sort_range(int* a, int lo, int hi) {
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

static void sort_int(int* a, int n) {
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

static int max_run_plus_one(int* bars, int barsSize) {
    if (barsSize <= 0) {
        return 1;
    }
    sort_int(bars, barsSize);
    int best = 1;
    int curr = 1;
    for (int i = 1; i < barsSize; ++i) {
        if (bars[i] == bars[i - 1]) {
            continue;
        }
        if (bars[i] == bars[i - 1] + 1) {
            ++curr;
            if (curr > best) {
                best = curr;
            }
        } else {
            curr = 1;
        }
    }
    return best + 1;
}

int maximizeSquareHoleArea(int n, int m, int* hBars, int hBarsSize, int* vBars, int vBarsSize) {
    (void)n;
    (void)m;
    int maxH = max_run_plus_one(hBars, hBarsSize);
    int maxV = max_run_plus_one(vBars, vBarsSize);
    int side = (maxH < maxV) ? maxH : maxV;
    long long area = (long long)side * (long long)side;
    return (int)area;
}
