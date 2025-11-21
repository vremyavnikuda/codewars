#include <vector>
#include <set>
#include <unordered_map>
#include <algorithm>

class Solution {
public:
    vector<int> findXSum(vector<int>& nums, int k, int x) {
        using pii = pair<int, int>;

        set<pii> topX;
        set<pii> remaining;
        int xSum = 0;
        unordered_map<int, int> frequency;
        auto addElement = [&](int value) {
            if (frequency[value] == 0) {
                return;
            }
            pii element = {frequency[value], value};
            if (!topX.empty() && element > *topX.begin()) {
                xSum += element.first * element.second;
                topX.insert(element);
            } else {
                remaining.insert(element);
            }
        };
        auto removeElement = [&](int value) {
            if (frequency[value] == 0) {
                return;
            }
            pii element = {frequency[value], value};
            auto it = topX.find(element);
            if (it != topX.end()) {
                xSum -= element.first * element.second;
                topX.erase(it);
            } else {
                remaining.erase(element);
            }
        };
        vector<int> result;
        for (int i = 0; i < nums.size(); ++i) {
            removeElement(nums[i]);
            ++frequency[nums[i]];
            addElement(nums[i]);
            int windowStart = i - k + 1;
            if (windowStart < 0) {
                continue;
            }
            while (!remaining.empty() && topX.size() < x) {
                pii largestRemaining = *remaining.rbegin();
                xSum += largestRemaining.first * largestRemaining.second;
                remaining.erase(largestRemaining);
                topX.insert(largestRemaining);
            }
            while (topX.size() > x) {
                pii smallestTop = *topX.begin();
                xSum -= smallestTop.first * smallestTop.second;
                topX.erase(smallestTop);
                remaining.insert(smallestTop);
            }
            result.push_back(xSum);
            removeElement(nums[windowStart]);
            --frequency[nums[windowStart]];
            addElement(nums[windowStart]);
        }
        return result;
    }
};

#include <iostream>
using namespace std;

int main() {
    Solution sol;
    vector<int> nums = {1, 1, 2, 2, 3, 4, 2, 3};
    int k = 6;
    int x = 2;
    
    cout << "Input: nums = [";
    for (size_t i = 0; i < nums.size(); i++) {
        cout << nums[i];
        if (i < nums.size() - 1) cout << ", ";
    }
    cout << "], k = " << k << ", x = " << x << endl;
    
    vector<int> result = sol.findXSum(nums, k, x);
    
    cout << "Result: [";
    for (size_t i = 0; i < result.size(); i++) {
        cout << result[i];
        if (i < result.size() - 1) cout << ", ";
    }
    cout << "]" << endl;
    
    return 0;
}
