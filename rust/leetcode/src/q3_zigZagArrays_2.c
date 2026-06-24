#include <stdlib.h>
#include <string.h>

#define MOD 1000000007

static void mat_pow_vec(int n, long long *Q, long long *v, int exp)
{
    long long *res = malloc(n * n * sizeof(long long));
    long long *tmp = malloc(n * n * sizeof(long long));
    long long *base = malloc(n * n * sizeof(long long));
    memcpy(base, Q, n * n * sizeof(long long));

    memset(res, 0, n * n * sizeof(long long));
    for (int i = 0; i < n; i++)
        res[i * n + i] = 1;

    while (exp)
    {
        if (exp & 1)
        {
            long long *t = malloc(n * n * sizeof(long long));
            memset(t, 0, n * n * sizeof(long long));
            for (int i = 0; i < n; i++)
                for (int k = 0; k < n; k++)
                    if (res[i * n + k])
                        for (int j = 0; j < n; j++)
                            t[i * n + j] = (t[i * n + j] + res[i * n + k] * base[k * n + j]) % MOD;
            memcpy(res, t, n * n * sizeof(long long));
            free(t);
        }
        memset(tmp, 0, n * n * sizeof(long long));
        for (int i = 0; i < n; i++)
            for (int k = 0; k < n; k++)
                if (base[i * n + k])
                    for (int j = 0; j < n; j++)
                        tmp[i * n + j] = (tmp[i * n + j] + base[i * n + k] * base[k * n + j]) % MOD;
        memcpy(base, tmp, n * n * sizeof(long long));
        exp >>= 1;
    }

    long long *nv = malloc(n * sizeof(long long));
    memset(nv, 0, n * sizeof(long long));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            nv[i] = (nv[i] + res[i * n + j] * v[j]) % MOD;
    memcpy(v, nv, n * sizeof(long long));

    free(nv);
    free(res);
    free(tmp);
    free(base);
}

static void apply_P(int n, long long *v)
{
    for (int i = 1; i < n; i++)
    {
        v[i] += v[i - 1];
        if (v[i] >= MOD) v[i] -= MOD;
    }
}

int zigZagArrays(int n, int l, int r)
{
    r -= l;
    if (r < 1) return 0;

    int R = r;

    if (R <= 100)
    {
        long long *v = malloc(R * sizeof(long long));
        for (int i = 0; i < R; i++)
            v[i] = 1;

        if (n <= 2)
        {
            apply_P(R, v);
            long long sum = 0;
            for (int i = 0; i < R; i++)
                sum = (sum + v[i]) % MOD;
            long long ans = (sum * 2) % MOD;
            free(v);
            return (int)ans;
        }

        long long *Q = malloc(R * R * sizeof(long long));
        for (int i = 0; i < R; i++)
            for (int j = 0; j < R; j++)
                Q[i * R + j] = R - (i > j ? i : j);

        if (n % 2 == 1)
        {
            int k = (n - 1) / 2;
            mat_pow_vec(R, Q, v, k);
        }
        else
        {
            int k = (n - 2) / 2;
            if (k > 0)
                mat_pow_vec(R, Q, v, k);
            apply_P(R, v);
        }

        long long sum = 0;
        for (int i = 0; i < R; i++)
            sum = (sum + v[i]) % MOD;
        long long ans = (sum * 2) % MOD;

        free(v);
        free(Q);
        return (int)ans;
    }

    int mod = MOD;
    int *prefix = malloc(R * sizeof(int));
    if (!prefix)
        return 0;

    int *p, *end;
    int i = 1, zig = 1;
    long long result = 0;

    p = prefix;
    end = prefix + R;
    while (p < end)
        *p++ = 1;

    p = prefix + 1;
    while (p < end)
        *p += p[-1], p++;

    for (; i < n - 1; i++)
    {
        if (zig)
        {
            p = prefix + R - 2;
            while (p >= prefix)
                *p += p[1], *p -= *p >= mod ? mod : 0, p--;
        }
        else
        {
            p = prefix + 1;
            while (p < end)
                *p += p[-1], *p -= *p >= mod ? mod : 0, p++;
        }
        zig ^= 1;
    }

    p = prefix;
    while (p < end)
        result += *p++;

    free(prefix);
    return (int)(result * 2 % mod);
}
