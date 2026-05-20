/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int *findThePrefixCommonArray(int *A, int ASize, int *B, int BSize, int *returnSize)
{
    int n = ASize, s = 0, i = 0, *r = (int *)malloc((*returnSize = n) * sizeof(int));
    char *v = (char *)calloc(n + 1, 1);
    for (; i < n; s += (v[A[i]] ^= 1) ^ 1, s += (v[B[i]] ^= 1) ^ 1, r[i++] = s)
        ;
    free(v);
    return r;
}
