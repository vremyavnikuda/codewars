#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <vector>
//
// Created by vremyavnikuda on 9/28/24.
//
/*int main() {
    int len;
    std::cin >> len;
    std::vector<int> arr(len);

    for (int i = 0; i < arr.size(); i++) {
        std::cin >> arr[i];
    }

    int count = 0;

    for (int i = 0; i < arr.size(); i++) {
        if (std::count(arr.begin(), arr.end(), arr[i]) == 1) {
            count++;
        }
    }

    std::cout << count << std::endl;

    return 0;
}*/

int main() {
    int len;
    std::cin >> len;
    std::vector<int> arr(len);

    for (int i = 0; i < len; i++) {
        std::cin >> arr[i];
    }

    std::unordered_map<int, int> frequency;

    for (int num : arr) {
        frequency[num]++;
    }

    int count = 0;

    for (const auto& pair : frequency) {
        if (pair.second == 1) {
            count++;
        }
    }

    std::cout << count << std::endl;

    return 0;
}