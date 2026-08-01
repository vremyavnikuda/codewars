#define Z(i) (*(nums + (i)))

int findMin(int* nums, int numsSize) {
    int l = 0, r = numsSize - 1, m, x, y;
    for (; l ^ r; x > y ? (l = m + 1) : x < y ? (r = m)
                                              : --r)
        m = (l + r) >> 1, x = Z(m), y = Z(r);
    return Z(l);
}
