long long maxTotalValue(int *n, int s, int k)
{
    int *e = n + s, m = *n, x = m;
    while (++n < e)
        x ^= (x ^ *n) & -(x < *n), m ^= (m ^ *n) & -(m > *n);
    return 1LL * k * (x - m);
}
