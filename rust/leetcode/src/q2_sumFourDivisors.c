#include <stdio.h>

int f(int x) {
  int c = 2, s = x + 1;
  for (int i = 2; i <= x / i; ++i) {
    if (x % i == 0) {
      ++c;
      s += i;
      if (i * i != x) {
        ++c;
        s += x / i;
      }
    }
  }
  return c == 4 ? s : 0;
}

int sumFourDivisors(int *nums, int numsSize) {
  int a = 0;
  for (int i = 0; i < numsSize; ++i) {
    a += f(nums[i]);
  }
  return a;
}

int main() {
  int n1[] = {21, 4, 7};
  int n2[] = {21, 21};
  int n3[] = {1, 2, 3, 4, 5};
  printf("%d\n", sumFourDivisors(n1, 3));
  printf("%d\n", sumFourDivisors(n2, 2));
  printf("%d\n", sumFourDivisors(n3, 5));
  return 0;
}