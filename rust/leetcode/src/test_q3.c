#include <stdio.h>
long long totalWaviness(long long, long long);
int main()
{
    struct
    {
        long long a, b, e;
    } t[] = {
        {120, 130, 3}, {198, 202, 3}, {4848, 4848, 2}, {1, 99, 0}, {100, 109, 9}, {100, 100, 0}, {1, 1, 0}, {999, 1001, 0}, {1000000000000000LL, 1000000000000000LL, 0}, {101, 101, 1}, {2549294942LL, 5067104447LL, 11661365485LL}, {1, 1000, 525}, {0, 0, 0}};
    for (int i = 0; t[i].a || t[i].b; i++)
    {
        long long r = totalWaviness(t[i].a, t[i].b);
        printf("%s: (%lld,%lld)=%lld (expected %lld)%s\n",
               r == t[i].e ? "OK" : "FAIL", t[i].a, t[i].b, r, t[i].e, r == t[i].e ? "" : " <--");
    }
    return 0;
}
