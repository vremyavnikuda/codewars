#include <stdbool.h>
#include <stdlib.h>
int _(const void *x, const void *y) { return *(int *)x - *(int *)y; }
bool asteroidsDestroyed(int mass, int *asteroids, int asteroidsSize)
{
    qsort(asteroids, asteroidsSize, sizeof *asteroids, _);
    long long M = mass;
    while (asteroidsSize-- && M >= *asteroids)
        M += *asteroids++;
    return !~asteroidsSize;
}
