long long maxSubarraySum(int *nums, int numsSize, int k)
{
    const long long neg = -(1LL << 62);
    long long base, mi, ma, di, da, ans;
    int i;
    if (numsSize <= 0)
        return 0;
    base = nums[0];
    mi = (long long)nums[0] * k;
    ma = neg;
    di = nums[0] / k;
    da = neg;
    ans = mi > di ? mi : di;
    for (i = 1; i < numsSize; ++i)
    {
        long long a = nums[i], m = a * k, d = nums[i] / k;
        long long nbase = base + a > a ? base + a : a;
        long long nmi = mi + m;
        long long nma = ma + a > mi + a ? ma + a : mi + a;
        long long ndi = di + d;
        long long nda = da + a > di + a ? da + a : di + a;
        if (base + m > nmi)
            nmi = base + m;
        if (m > nmi)
            nmi = m;
        if (base + d > ndi)
            ndi = base + d;
        if (d > ndi)
            ndi = d;
        base = nbase;
        mi = nmi;
        ma = nma;
        di = ndi;
        da = nda;
        if (mi > ans)
            ans = mi;
        if (ma > ans)
            ans = ma;
        if (di > ans)
            ans = di;
        if (da > ans)
            ans = da;
    }
    return ans;
}
