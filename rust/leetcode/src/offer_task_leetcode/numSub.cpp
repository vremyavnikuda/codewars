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

#inc
lude <iostream>
#include <string>
using namespace std;

int main() {
    Solution sol;
    string s1 = "0110111";
    cout << "Input: " << s1 << endl;
    cout << "Result: " << sol.numSub(s1) << endl;
    
    string s2 = "101";
    cout << "\nInput: " << s2 << endl;
    cout << "Result: " << sol.numSub(s2) << endl;
    
    string s3 = "111111";
    cout << "\nInput: " << s3 << endl;
    cout << "Result: " << sol.numSub(s3) << endl;
    
    return 0;
}
