#include <string>
#include <algorithm>
class Solution {
public:
    int minimumDeletions(const std::string& s) {
        int lb = 0, ra = std::count(s.begin(), s.end(), 'a');
        int ans = ra;
        for (char c : s) {
            ra -= c == 'a';
            ans = std::min(ans, lb + ra);
            lb += c == 'b';
        }
        return ans;
    }
};