#include <stdlib.h>
typedef long long L;
#define X(a, b) (a > b ? a : b)
#define N(a, b) (a < b ? a : b)
#define Y(l, r) ({int _a=l,_b=r,_c=g[_b-_a+1];(L)(X(A[_a*M+_c],A[(_b-(1<<_c)+1)*M+_c])-N(I[_a*M+_c],I[(_b-(1<<_c)+1)*M+_c])); })
#define PH(v, l, r)                 \
    do                              \
    {                               \
        H[hn] = v;                  \
        HL[hn] = l;                 \
        HR[hn] = r;                 \
        int _i = hn++;              \
        while (_i)                  \
        {                           \
            int _p = (_i - 1) >> 1; \
            if (H[_i] > H[_p])      \
            {                       \
                L _t = H[_i];       \
                H[_i] = H[_p];      \
                H[_p] = _t;         \
                int _s = HL[_i];    \
                HL[_i] = HL[_p];    \
                HL[_p] = _s;        \
                _s = HR[_i];        \
                HR[_i] = HR[_p];    \
                HR[_p] = _s;        \
                _i = _p;            \
            }                       \
            else                    \
                break;              \
        }                           \
    } while (0)
#define PP()                                              \
    do                                                    \
    {                                                     \
        H[0] = H[--hn];                                   \
        HL[0] = HL[hn];                                   \
        HR[0] = HR[hn];                                   \
        int _i = 0;                                       \
        while (1)                                         \
        {                                                 \
            int _b = _i, _l = (_i << 1) + 1, _r = _l + 1; \
            if (_l < hn && H[_l] > H[_b])                 \
                _b = _l;                                  \
            if (_r < hn && H[_r] > H[_b])                 \
                _b = _r;                                  \
            if (_b != _i)                                 \
            {                                             \
                L _t = H[_i];                             \
                H[_i] = H[_b];                            \
                H[_b] = _t;                               \
                int _s = HL[_i];                          \
                HL[_i] = HL[_b];                          \
                HL[_b] = _s;                              \
                _s = HR[_i];                              \
                HR[_i] = HR[_b];                          \
                HR[_b] = _s;                              \
                _i = _b;                                  \
            }                                             \
            else                                          \
                break;                                    \
        }                                                 \
    } while (0)

long long maxTotalValue(int *nums, int numsSize, int k)
{
    if (!numsSize || !k)
        return 0;
    int n = numsSize, *m = nums;
    int *g = (int *)malloc((n + 1) << 2), j, o, p, hn = 0;
    g[0] = g[1] = 0;
    for (j = 2; j <= n; j++)
        g[j] = g[j >> 1] + 1;
    int M = g[n] + 2, *A = (int *)malloc(n * M << 3), *I = A + n * M;
    for (j = 0; j < n; j++)
        A[j * M] = I[j * M] = m[j];
    for (j = 1; j < M; j++)
        for (o = 1 << (j - 1), p = 0; p <= n - (1 << j); p++)
            A[p * M + j] = X(A[p * M + j - 1], A[(p + o) * M + j - 1]),
                      I[p * M + j] = N(I[p * M + j - 1], I[(p + o) * M + j - 1]);
    L *H = (L *)malloc(n * (sizeof(L) + 8));
    int *HL = (int *)(H + n), *HR = HL + n;
    L ans = 0;
    for (j = 0; j < n; j++)
        PH(Y(j, n - 1), j, n - 1);
    while (k-- && hn)
    {
        ans += H[0];
        int l = HL[0], r = HR[0];
        PP();
        if (r > l)
            PH(Y(l, r - 1), l, r - 1);
    }
    free(g);
    free(A);
    free(H);
    return ans;
}
