#include <string>
class Solution {
public:
    int longestBalanced(string s) {
        const int n = (int)s.size();
        if (n < 2) return n;
        int b[26], z[26] = {};
        int p = 1, r = 0;
        for (int i = 0; i < n; ++i, ++p) {
            if (n - i <= r) break;
            int m = 0, u = 0;
            for (int j = i; j < n; ++j) {
                int q = (s[j] & 31) - 1;
                if (z[q] != p) {
                    z[q] = p;
                    b[q] = 0;
                }
                const int t = ++b[q];
                u += (t == 1);
                m = (m < t ? t : m);
                const int len = j - i + 1;
                if ((m * u) != len) continue;
                r = (r < len ? len : r);
            }
        }
        return r;
    }
};
