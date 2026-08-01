#include <string.h>
#include <stdlib.h>
#define F for
#define I if
#define R return
#define B break
int *stringIndices(char **w, int n, char **q, int m, int *s)
{
    int i, j, k, c, u, v, t, *a, *b, *r;
    F(a = (int *)malloc(n << 2), t = i = 0; i < n; a[i] = strlen(w[i]), t += a[i++]);
    F(b = (int *)calloc(++t * 0x1B, 4), j = 0; j < 0x1A; b[j++] = ~0);
    F(t = i = 0; i < n; i++)
    {
        u = 0;
        F(k = a[i]; k--; u = v)
        {
            c = w[i][k] - 0x61;
            I((v = c[u * 0x1B + b]) < 0)
            {
                c[u * 0x1B + b] = v = ++t;
                F(j = 0; j < 0x1A; j[v * 0x1B + b] = ~0, j++);
                0x1A [v * 0x1B + b] = i;
            }
            I(a[i] < a[j = 0x1A [v * 0x1B + b]] | a[i] == a[j] & i < j)
            0x1A [v * 0x1B + b] = i;
        }
        I(a[i] < a[j = b[0x1A]] | a[i] == a[j] & i < j)
        b[0x1A] = i;
    }
    F(r = (int *)malloc(m << 2), *s = m, i = 0; i < m; i++)
    {
        u = 0;
        F(k = strlen(q[i]); k--; u = v)
        I((v = (c = q[i][k] - 0x61)[u * 0x1B + b]) < 0)
        B;
        r[i] = 0x1A [u * 0x1B + b];
    }
    free(a);
    free(b);
    R r;
}
