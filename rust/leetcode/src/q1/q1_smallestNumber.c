int smallestNumber(int n, int t) {
    for (int q1 = n;; ++q1) {
        int q2 = 1;
        for (int q3 = q1; q3 > 0; q3 /= 10) {
            q2 *= (q3 % 10);
        }
        if (q2 % t == 0) {
            return q1;
        }
    }
}
