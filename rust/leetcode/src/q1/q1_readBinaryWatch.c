/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
#include <stdlib.h>

static inline int popcount_int(int x) {
#if defined(__GNUC__) || defined(__clang__)
    return __builtin_popcount((unsigned int)x);
#else
    int cnt = 0;
    while (x) {
        x &= (x - 1);
        ++cnt;
    }
    return cnt;
#endif
}

static char* format_time(int hour, int minute) {
    char* s = (char*)malloc(6); /* "h:mm" or "hh:mm" + '\0' */
    int pos = 0;
    if (hour >= 10) {
        s[pos++] = '1';
        s[pos++] = (char)('0' + (hour - 10));
    } else {
        s[pos++] = (char)('0' + hour);
    }
    s[pos++] = ':';
    s[pos++] = (char)('0' + (minute / 10));
    s[pos++] = (char)('0' + (minute % 10));
    s[pos] = '\0';
    return s;
}

char** readBinaryWatch(int turnedOn, int* returnSize) {
    int hourBits[12];
    int minBits[60];
    int i, j;
    int count = 0;

    *returnSize = 0;
    if (turnedOn < 0 || turnedOn > 8) {
        return (char**)malloc(0);
    }

    for (i = 0; i < 12; ++i) {
        hourBits[i] = popcount_int(i);
    }
    for (j = 0; j < 60; ++j) {
        minBits[j] = popcount_int(j);
    }

    for (i = 0; i < 12; ++i) {
        for (j = 0; j < 60; ++j) {
            if (hourBits[i] + minBits[j] == turnedOn) {
                ++count;
            }
        }
    }

    if (count == 0) {
        return (char**)malloc(0);
    }

    char** res = (char**)malloc(sizeof(char*) * (size_t)count);
    int idx = 0;
    for (i = 0; i < 12; ++i) {
        for (j = 0; j < 60; ++j) {
            if (hourBits[i] + minBits[j] == turnedOn) {
                res[idx++] = format_time(i, j);
            }
        }
    }

    *returnSize = count;
    return res;
}
