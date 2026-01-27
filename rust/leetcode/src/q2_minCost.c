#include <limits.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int *d;
    int *u;
    int s;
    int c;
} k;

static void k1(k *h, int i) {
    while (i > 1) {
        int p = i >> 1;
        if (h->d[p] <= h->d[i]) break;
        int td = h->d[p], tu = h->u[p];
        h->d[p] = h->d[i]; h->u[p] = h->u[i];
        h->d[i] = td;      h->u[i] = tu;
        i = p;
    }
}

static void k2(k *h, int i) {
    for (;;) {
        int l = i << 1;
        if (l > h->s) break;
        int r = l + 1;
        int m = (r <= h->s && h->d[r] < h->d[l]) ? r : l;
        if (h->d[i] <= h->d[m]) break;
        int td = h->d[m], tu = h->u[m];
        h->d[m] = h->d[i]; h->u[m] = h->u[i];
        h->d[i] = td;      h->u[i] = tu;
        i = m;
    }
}

static void k3(k *h, int dd, int uu) {
    if (h->s + 1 >= h->c) {
        int nc = h->c << 1;
        size_t bs = (size_t)(h->s + 1) * sizeof(int);
        int *nd = (int *)malloc((size_t)nc * sizeof(int));
        int *nu = (int *)malloc((size_t)nc * sizeof(int));
        if (!nd || !nu) {
            free(nd); free(nu);
            return;
        }
        memcpy(nd, h->d, bs);
        memcpy(nu, h->u, bs);
        free(h->d); free(h->u);
        h->d = nd; h->u = nu; h->c = nc;
    }
    int i = ++h->s;
    h->d[i] = dd; h->u[i] = uu;
    k1(h, i);
}

static int k4(k *h, int *dd, int *uu) {
    if (h->s == 0) return 0;
    *dd = h->d[1];
    *uu = h->u[1];
    h->d[1] = h->d[h->s];
    h->u[1] = h->u[h->s];
    h->s--;
    k2(h, 1);
    return 1;
}

int minCost(int n, int** edges, int edgesSize, int* edgesColSize) {
    (void)edgesColSize;
    if (n <= 0) return -1;
    if (n == 1) return 0;

    int m = edgesSize;
    int e = m << 1;

    int *h = (int *)malloc((size_t)n * sizeof(int));
    int *t = (int *)malloc((size_t)e * sizeof(int));
    int *w = (int *)malloc((size_t)e * sizeof(int));
    int *nx = (int *)malloc((size_t)e * sizeof(int));
    int *di = (int *)malloc((size_t)n * sizeof(int));
    if (!h || !t || !w || !nx || !di) {
        free(h); free(t); free(w); free(nx); free(di);
        return -1;
    }

    for (int i = 0; i < n; i++) h[i] = -1;

    int z = 0;
    for (int i = 0; i < m; i++) {
        int a = edges[i][0];
        int b = edges[i][1];
        int c = edges[i][2];

        t[z] = b; w[z] = c;     nx[z] = h[a]; h[a] = z++;
        t[z] = a; w[z] = c << 1; nx[z] = h[b]; h[b] = z++;
    }

    const int inf = INT_MAX / 4;
    for (int i = 0; i < n; i++) di[i] = inf;
    di[0] = 0;

    int cap = (e + n + 8);
    if (cap < 32) cap = 32;
    k q = {
        .d = (int *)malloc((size_t)cap * sizeof(int)),
        .u = (int *)malloc((size_t)cap * sizeof(int)),
        .s = 0,
        .c = cap
    };
    if (!q.d || !q.u) {
        free(h); free(t); free(w); free(nx); free(di);
        free(q.d); free(q.u);
        return -1;
    }

    k3(&q, 0, 0);

    int cd, cu;
    while (k4(&q, &cd, &cu)) {
        if (cd != di[cu]) continue;
        if (cu == n - 1) {
            free(h); free(t); free(w); free(nx); free(di);
            free(q.d); free(q.u);
            return cd;
        }

        for (int i = h[cu]; i != -1; i = nx[i]) {
            int v = t[i];
            int nd = cd + w[i];
            if (nd < di[v]) {
                di[v] = nd;
                k3(&q, nd, v);
            }
        }
    }

    free(h); free(t); free(w); free(nx); free(di);
    free(q.d); free(q.u);
    return -1;
}
