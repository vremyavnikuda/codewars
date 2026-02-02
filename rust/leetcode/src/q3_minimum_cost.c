#include <stdint.h>
#include <stdlib.h>

typedef struct {
    int k;
    int c;
    int s;
    int l;
    int r;
    uint32_t p;
} n;

typedef struct {
    n *a;
    int z;
    int r;
    uint32_t x;
} t;

static inline int g(t *q, int i) {
    return i ? q->a[i].s : 0;
}

static inline void u(t *q, int i) {
    if (i) q->a[i].s = q->a[i].c + g(q, q->a[i].l) + g(q, q->a[i].r);
}

static inline uint32_t xr(t *q) {
    uint32_t x = q->x;
    x ^= x << 13;
    x ^= x >> 17;
    x ^= x << 5;
    q->x = x;
    return x;
}

static int nw(t *q, int k) {
    int i = ++q->z;
    q->a[i].k = k;
    q->a[i].c = 1;
    q->a[i].s = 1;
    q->a[i].l = 0;
    q->a[i].r = 0;
    q->a[i].p = xr(q);
    return i;
}

static int rr(t *q, int y) {
    int x = q->a[y].l;
    q->a[y].l = q->a[x].r;
    q->a[x].r = y;
    u(q, y);
    u(q, x);
    return x;
}

static int rl(t *q, int x) {
    int y = q->a[x].r;
    q->a[x].r = q->a[y].l;
    q->a[y].l = x;
    u(q, x);
    u(q, y);
    return y;
}

static int ins(t *q, int x, int k) {
    if (!x) return nw(q, k);
    if (q->a[x].k == k) {
        q->a[x].c++;
        q->a[x].s++;
        return x;
    }
    if (k < q->a[x].k) {
        q->a[x].l = ins(q, q->a[x].l, k);
        if (q->a[x].l && q->a[q->a[x].l].p > q->a[x].p) x = rr(q, x);
    } else {
        q->a[x].r = ins(q, q->a[x].r, k);
        if (q->a[x].r && q->a[q->a[x].r].p > q->a[x].p) x = rl(q, x);
    }
    u(q, x);
    return x;
}

static int mg(t *q, int a, int b) {
    if (!a) return b;
    if (!b) return a;
    if (q->a[a].p > q->a[b].p) {
        q->a[a].r = mg(q, q->a[a].r, b);
        u(q, a);
        return a;
    }
    q->a[b].l = mg(q, a, q->a[b].l);
    u(q, b);
    return b;
}

static int era(t *q, int x, int k, int *ok) {
    if (!x) return 0;
    if (k == q->a[x].k) {
        *ok = 1;
        if (q->a[x].c > 1) {
            q->a[x].c--;
            q->a[x].s--;
            return x;
        }
        return mg(q, q->a[x].l, q->a[x].r);
    }
    if (k < q->a[x].k) q->a[x].l = era(q, q->a[x].l, k, ok);
    else q->a[x].r = era(q, q->a[x].r, k, ok);
    if (*ok) u(q, x);
    return x;
}

static int hs(t *q, int x, int k) {
    while (x) {
        int v = q->a[x].k;
        if (k == v) return 1;
        x = (k < v) ? q->a[x].l : q->a[x].r;
    }
    return 0;
}

static int mn(t *q, int x) {
    while (q->a[x].l) x = q->a[x].l;
    return q->a[x].k;
}

static int mx(t *q, int x) {
    while (q->a[x].r) x = q->a[x].r;
    return q->a[x].k;
}

static inline int sz(t *q) {
    return q->r ? q->a[q->r].s : 0;
}

long long minimumCost(int* nums, int numsSize, int k, int dist) {
    int n0 = numsSize;
    if (n0 <= 0) return 0;
    int kk = k - 1;
    if (kk <= 0) return (long long)nums[0];
    int cap = (n0 << 1) + 8;
    if (cap < 16) cap = 16;
    t l = {0}, r = {0};
    l.a = (n *)malloc((size_t)cap * sizeof(n));
    r.a = (n *)malloc((size_t)cap * sizeof(n));
    if (!l.a || !r.a) {
        free(l.a);
        free(r.a);
        return 0;
    }
    l.x = 0x9e3779b9u ^ (uint32_t)n0;
    r.x = 0x85ebca6bu ^ (uint32_t)(n0 << 1);
    int b = dist + 2;
    long long s = 0;
    for (int i = 0; i < b; i++) s += nums[i];
    for (int i = 1; i < b; i++) l.r = ins(&l, l.r, nums[i]);
    while (sz(&l) > kk) {
        int v = mx(&l, l.r);
        int ok = 0;
        l.r = era(&l, l.r, v, &ok);
        s -= v;
        r.r = ins(&r, r.r, v);
    }
    long long ans = s;
    for (int i = b; i < n0; i++) {
        int x = nums[i - dist - 1];
        if (hs(&l, l.r, x)) {
            int ok = 0;
            l.r = era(&l, l.r, x, &ok);
            s -= x;
        } else {
            int ok = 0;
            r.r = era(&r, r.r, x, &ok);
        }
        int y = nums[i];
        if (!l.r) {
            l.r = ins(&l, l.r, y);
            s += y;
        } else if (y < mx(&l, l.r)) {
            l.r = ins(&l, l.r, y);
            s += y;
        } else {
            r.r = ins(&r, r.r, y);
        }
        while (sz(&l) < kk) {
            int v = mn(&r, r.r);
            int ok = 0;
            r.r = era(&r, r.r, v, &ok);
            l.r = ins(&l, l.r, v);
            s += v;
        }
        while (sz(&l) > kk) {
            int v = mx(&l, l.r);
            int ok = 0;
            l.r = era(&l, l.r, v, &ok);
            s -= v;
            r.r = ins(&r, r.r, v);
        }
        if (s < ans) ans = s;
    }
    free(l.a);
    free(r.a);
    return ans;
}
