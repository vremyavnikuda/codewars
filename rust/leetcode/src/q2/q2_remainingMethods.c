#include <stdlib.h>
#include <string.h>

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* remainingMethods(int n, int k, int** invocations, int invocationsSize, int* invocationsColSize, int* returnSize) {
    int q1 = invocationsSize, q2[n + 1], q3[q1 + 1], q4[n], q5[n];
    memset(q2, 0, sizeof q2);
    for (int i = 0; i < q1; ++i)
        ++q2[invocations[i][0]];
    int q8 = 0;
    for (int i = 0; i < n; ++i) {
        int q9 = q2[i];
        q2[i] = q8;
        q8 += q9;
    }
    q2[n] = q8;
    memcpy(q4, q2, n * sizeof(int));
    for (int i = 0; i < q1; ++i)
        q3[q4[invocations[i][0]]++] = invocations[i][1];
    unsigned char q6[n];
    memset(q6, 0, sizeof q6);
    int q7 = 0;
    q5[q7++] = k;
    q6[k] = 1;
    while (q7) {
        int i = q5[--q7];
        for (int e = q2[i]; e < q2[i + 1]; ++e)
            if (!q6[q3[e]]) {
                q6[q3[e]] = 1;
                q5[q7++] = q3[e];
            }
    }
    int q10 = 0;
    for (int i = 0; i < q1; ++i)
        if (!q6[invocations[i][0]] && q6[invocations[i][1]])
            q10 = 1;
    /* ponytail: keep-all iff non-suspicious invokes suspicious; the undirected graph of the C++ original is unnecessary */
    int* q9 = malloc(n * sizeof(int));
    int q11 = 0;
    for (int i = 0; i < n; ++i)
        if (q10 || !q6[i])
            q9[q11++] = i;
    *returnSize = q11;
    return q9;
}
