static int cmp_i(const void *a, const void *b) {
    int x = *(const int *)a;
    int y = *(const int *)b;
    return (x > y) - (x < y);
}

#include <stdlib.h>

int minimumDifference(int* nums, int numsSize, int k) {
    int i;
    int a;
    if (k <= 1 || numsSize <= 1) {
        return 0;
    }
    qsort(nums, (size_t)numsSize, sizeof(int), cmp_i);
    a = nums[ k - 1 ] - nums[ 0 ];
    for (i = 1; i <= numsSize - k; ++i) {
        int b = nums[ i + k - 1 ] - nums[ i ];
        if (b < a) {
            a = b;
        }
    }
    return a;
}
