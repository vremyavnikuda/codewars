int minElement(int *nums, int n)
{
    int m = ~0u >> 1, x;
    while (n--)
    {
        x = *nums++;
        x = x % 10 + ((x /= 10), x % 10) + ((x /= 10), x % 10) + ((x /= 10), x % 10) + ((x /= 10), x % 10);
        m = m < x ? m : x;
    }
    return m;
}
