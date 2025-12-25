#include <stdio.h>
#include <stdlib.h>

void sw(int *a, int *b) {
  int t = *a;
  *a = *b;
  *b = t;
}

int pt(int *arr, int l, int r) {
  int p = arr[r];
  int i = l;

  for (int j = l; j < r; ++j) {
    if (arr[j] >= p) {
      sw(&arr[i], &arr[j]);
      ++i;
    }
  }

  sw(&arr[i], &arr[r]);
  return i;
}

void qs(int *arr, int l, int r, int k) {
  if (l >= r)
    return;

  int p = pt(arr, l, r);

  if (p == k)
    return;
  if (p > k) {
    qs(arr, l, p - 1, k);
  } else {
    qs(arr, p + 1, r, k);
  }
}

int cmp(const void *a, const void *b) { return *(int *)b - *(int *)a; }

long long maximumHappinessSum(int *happiness, int happinessSize, int k) {
  qs(happiness, 0, happinessSize - 1, k - 1);
  qsort(happiness, k, sizeof(int), cmp);

  long long a = 0;

  for (int i = 0; i < k; ++i) {
    int x = happiness[i] - i;
    if (x > 0) {
      a += x;
    }
  }

  return a;
}

int main() {
  int h1[] = {1, 2, 3};
  int h2[] = {1, 1, 1, 1};
  int h3[] = {2, 3, 4, 5};

  printf("%lld\n", maximumHappinessSum(h1, 3, 2));
  printf("%lld\n", maximumHappinessSum(h2, 4, 2));
  printf("%lld\n", maximumHappinessSum(h3, 4, 1));

  return 0;
}
