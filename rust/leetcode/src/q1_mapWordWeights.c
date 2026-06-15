#include <stdlib.h>

char *mapWordWeights(char **A, int B, int *C, int D)
{
    char *E, *F;
    int G, H, I;
    if (!(E = (char *)malloc(B + 1)))
        return 0;
    for (F = E, G = 0; G < B; G++)
    {
        H = 0;
        I = 0;
        while (A[G][I])
            H = (H + C[A[G][I++] - 97]) % 26;
        *F++ = 122 - H;
    }
    *F = 0;
    return E;
}