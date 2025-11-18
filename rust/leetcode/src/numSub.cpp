class Solution {
public:
    int numSub(string s) {
       long long len=0;
       long long result=0;
        for (auto c : s) {
            if (c=='1') {
                len++;
                continue;
            }
            if (len > 0){
                result += len*(len+1)/2;
                len = 0;
            }
        }
        result += len*(len+1)/2;
        return result % 1000000007 ;
    }
};