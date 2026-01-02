#include <stdio.h>

int repeatedNTimes(int *n, int s) {
  int i = 1;
  while (++i < s)
    if (n[i] == n[i - 1] || n[i] == n[i - 2])
      return n[i];
  return n[0];
}

int main() {
  int n1[] = {1, 2, 3, 3};
  int n2[] = {2, 1, 2, 5, 3, 2};
  int n3[] = {5, 1, 5, 2, 5, 3, 5, 4};

  printf("%d\n", repeatedNTimes(n1, 4));
  printf("%d\n", repeatedNTimes(n2, 6));
  printf("%d\n", repeatedNTimes(n3, 8));

  return 0;
}
