#include <stdio.h>
#include <stdlib.h>

int minPairSum(int *nums, int numsSize) {
  static int cnt[100001];
  for (int i = 0; i < 100001; ++i) cnt[i] = 0;
  for (int i = 0; i < numsSize; ++i) {
    ++cnt[nums[i]];
  }
  int l = 1, r = 100000;
  int ans = 0;
  int p = numsSize / 2;
  while (p > 0) {
    while (l <= r && cnt[l] == 0) ++l;
    while (l <= r && cnt[r] == 0) --r;
    if (l > r) break;
    int t = l + r;
    ans = ans > t ? ans : t;

    --cnt[l];
    --cnt[r];
    --p;
  }
  return ans;
}

int main() {
  int a1[] = {3, 5, 2, 3};
  int a2[] = {3, 5, 4, 2, 4, 6};
  printf("%d\n", minPairSum(a1, 4));
  printf("%d\n", minPairSum(a2, 6));
  return 0;
}
