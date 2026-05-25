#include <stdbool.h>
#include <string.h>
#define G(x) ((f[(x) >> 3] >> ((x) & 7)) & 1)
#define S(x) (f[(x) >> 3] |= (unsigned char)(1u << ((x) & 7)))
bool canReach(char *s, int minJump, int maxJump)
{
    int n = strlen(s), c = 0, i = 1, a, b;
    unsigned char f[(n + 7) >> 3];
    memset(f, 0, (n + 7) >> 3);
    S(0);
    for (; i < n; ++i)
        a = i - minJump,
        b = i - maxJump - 1,
        a >= 0 && (c += G(a)),
        b >= 0 && (c -= G(b)),
        s[i] == 48 && c && S(i);
    return G(n - 1);
}
