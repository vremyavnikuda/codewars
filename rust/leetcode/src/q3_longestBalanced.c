#include <stdlib.h>
#include <stdint.h>

typedef struct {
    int n;
    int *mn;
    int *mx;
    int *lazy;
} SegmentTree;

static inline int min_int(int a, int b) { return a < b ? a : b; }
static inline int max_int(int a, int b) { return a > b ? a : b; }

static void st_init(SegmentTree *st, int n) {
    int size = (n + 1) << 2;
    st->n = n;
    st->mn = (int *)calloc((size_t)size, sizeof(int));
    st->mx = (int *)calloc((size_t)size, sizeof(int));
    st->lazy = (int *)calloc((size_t)size, sizeof(int));
}

static void st_free(SegmentTree *st) {
    free(st->mn);
    free(st->mx);
    free(st->lazy);
    st->mn = st->mx = st->lazy = NULL;
    st->n = 0;
}

static inline void st_apply(SegmentTree *st, int u, int v) {
    st->mn[u] += v;
    st->mx[u] += v;
    st->lazy[u] += v;
}

static inline void st_pushup(SegmentTree *st, int u) {
    int lc = u << 1;
    int rc = lc | 1;
    st->mn[u] = min_int(st->mn[lc], st->mn[rc]);
    st->mx[u] = max_int(st->mx[lc], st->mx[rc]);
}

static inline void st_pushdown(SegmentTree *st, int u) {
    int tag = st->lazy[u];
    if (tag != 0) {
        st_apply(st, u << 1, tag);
        st_apply(st, u << 1 | 1, tag);
        st->lazy[u] = 0;
    }
}

static void st_modify(SegmentTree *st, int u, int l, int r, int ql, int qr, int v) {
    if (ql <= l && r <= qr) {
        st_apply(st, u, v);
        return;
    }
    st_pushdown(st, u);
    int mid = (l + r) >> 1;
    if (ql <= mid) st_modify(st, u << 1, l, mid, ql, qr, v);
    if (qr > mid) st_modify(st, u << 1 | 1, mid + 1, r, ql, qr, v);
    st_pushup(st, u);
}

static int st_query(SegmentTree *st, int u, int l, int r, int target) {
    if (l == r) return l;
    st_pushdown(st, u);
    int lc = u << 1;
    int rc = lc | 1;
    if (st->mn[lc] <= target && target <= st->mx[lc]) {
        return st_query(st, lc, l, (l + r) >> 1, target);
    }
    return st_query(st, rc, ((l + r) >> 1) + 1, r, target);
}

typedef struct {
    int cap;
    int *keys;
    int *vals;
    unsigned char *used;
} IntIntMap;

static inline uint32_t hash_int(int key) {
    return (uint32_t)key * 2654435761u;
}

static void map_init(IntIntMap *m, int expected) {
    int cap = 1;
    int need = expected > 0 ? expected * 4 : 4;
    while (cap < need) cap <<= 1;
    m->cap = cap;
    m->keys = (int *)malloc((size_t)cap * sizeof(int));
    m->vals = (int *)malloc((size_t)cap * sizeof(int));
    m->used = (unsigned char *)calloc((size_t)cap, sizeof(unsigned char));
}

static void map_free(IntIntMap *m) {
    free(m->keys);
    free(m->vals);
    free(m->used);
    m->keys = m->vals = NULL;
    m->used = NULL;
    m->cap = 0;
}

static int map_get(const IntIntMap *m, int key, int *out) {
    uint32_t mask = (uint32_t)m->cap - 1u;
    uint32_t idx = hash_int(key) & mask;
    while (m->used[idx]) {
        if (m->keys[idx] == key) {
            *out = m->vals[idx];
            return 1;
        }
        idx = (idx + 1) & mask;
    }
    return 0;
}

static void map_set(IntIntMap *m, int key, int val) {
    uint32_t mask = (uint32_t)m->cap - 1u;
    uint32_t idx = hash_int(key) & mask;
    while (m->used[idx]) {
        if (m->keys[idx] == key) {
            m->vals[idx] = val;
            return;
        }
        idx = (idx + 1) & mask;
    }
    m->used[idx] = 1;
    m->keys[idx] = key;
    m->vals[idx] = val;
}

static int longestBalanced_impl(const int *nums, int numsSize) {
    if (numsSize <= 0) return 0;

    SegmentTree st;
    IntIntMap last;
    st_init(&st, numsSize);
    map_init(&last, numsSize);

    int now = 0;
    int ans = 0;

    for (int i = 1; i <= numsSize; ++i) {
        int x = nums[i - 1];
        int det = (x & 1) ? 1 : -1;
        int prev;

        if (map_get(&last, x, &prev)) {
            st_modify(&st, 1, 0, numsSize, prev, numsSize, -det);
            now -= det;
        }

        map_set(&last, x, i);
        st_modify(&st, 1, 0, numsSize, i, numsSize, det);
        now += det;

        int pos = st_query(&st, 1, 0, numsSize, now);
        int len = i - pos;
        if (len > ans) ans = len;
    }

    map_free(&last);
    st_free(&st);
    return ans;
}

int longestBalanced(int* nums, int numsSize) {
    return longestBalanced_impl(nums, numsSize);

}
