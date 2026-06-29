/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
#include <stdlib.h>

static int heap_less(long long ta, int sa, long long tb, int sb)
{
    return ta < tb || (ta == tb && sa < sb);
}

static void heap_push(long long *ht, int *hs, int *hn, long long t, int s)
{
    int i = (*hn)++;
    while (i > 0)
    {
        int p = (i - 1) >> 1;
        if (!heap_less(t, s, ht[p], hs[p]))
            break;
        ht[i] = ht[p];
        hs[i] = hs[p];
        i = p;
    }
    ht[i] = t;
    hs[i] = s;
}

static void heap_pop(long long *ht, int *hs, int *hn, long long *t, int *s)
{
    long long lt;
    int ls, i = 0;
    *t = ht[0];
    *s = hs[0];
    --*hn;
    if (*hn <= 0)
        return;
    lt = ht[*hn];
    ls = hs[*hn];
    while (1)
    {
        int l = (i << 1) + 1, r = l + 1, b = l;
        if (l >= *hn)
            break;
        if (r < *hn && heap_less(ht[r], hs[r], ht[l], hs[l]))
            b = r;
        if (!heap_less(ht[b], hs[b], lt, ls))
            break;
        ht[i] = ht[b];
        hs[i] = hs[b];
        i = b;
    }
    ht[i] = lt;
    hs[i] = ls;
}

long long *minTimeMaxPower(int n, int **edges, int edgesSize, int *edgesColSize, int power, int *cost, int costSize, int source, int target, int *returnSize)
{
    const long long inf = 1LL << 62;
    int stride = power + 1, states = n * stride;
    int *head, *to, *next, *wt, i, hn = 0, bestPower = -1;
    long long *ans = (long long *)malloc(2 * sizeof(*ans));
    long long *dist, *ht, bestTime = -1;
    int *hs;
    long long heapCap = 1;
    (void)edgesColSize;
    (void)costSize;
    *returnSize = 2;
    if (source == target)
    {
        ans[0] = 0;
        ans[1] = power;
        return ans;
    }
    head = (int *)malloc((size_t)n * sizeof(*head));
    to = (int *)malloc((size_t)edgesSize * sizeof(*to));
    next = (int *)malloc((size_t)edgesSize * sizeof(*next));
    wt = (int *)malloc((size_t)edgesSize * sizeof(*wt));
    dist = (long long *)malloc((size_t)states * sizeof(*dist));
    for (i = 0; i < n; ++i)
        head[i] = -1;
    for (i = 0; i < edgesSize; ++i)
    {
        int u = edges[i][0];
        to[i] = edges[i][1];
        wt[i] = edges[i][2];
        next[i] = head[u];
        head[u] = i;
        if (cost[u] <= power)
            heapCap += power - cost[u] + 1;
    }
    ht = (long long *)malloc((size_t)heapCap * sizeof(*ht));
    hs = (int *)malloc((size_t)heapCap * sizeof(*hs));
    for (i = 0; i < states; ++i)
        dist[i] = inf;
    dist[source * stride + power] = 0;
    heap_push(ht, hs, &hn, 0, source * stride + power);
    while (hn > 0)
    {
        long long time;
        int state, u, p, e;
        heap_pop(ht, hs, &hn, &time, &state);
        if (time != dist[state])
            continue;
        if (bestTime >= 0 && time > bestTime)
            break;
        u = state / stride;
        p = state - u * stride;
        if (u == target)
        {
            bestTime = time;
            if (p > bestPower)
                bestPower = p;
            continue;
        }
        if (bestTime >= 0 || p < cost[u])
            continue;
        p -= cost[u];
        for (e = head[u]; e != -1; e = next[e])
        {
            int ns = to[e] * stride + p;
            long long nt = time + wt[e];
            if (nt < dist[ns])
            {
                dist[ns] = nt;
                heap_push(ht, hs, &hn, nt, ns);
            }
        }
    }
    if (bestPower < 0)
    {
        ans[0] = -1;
        ans[1] = -1;
    }
    else
    {
        ans[0] = bestTime;
        ans[1] = bestPower;
    }
    free(head);
    free(to);
    free(next);
    free(wt);
    free(dist);
    free(ht);
    free(hs);
    return ans;
}
