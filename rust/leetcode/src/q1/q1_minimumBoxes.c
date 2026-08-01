#include <stdlib.h>
int cmp(const void *a, const void *b) { return *(int *)b - *(int *)a; }

int minimumBoxes(int *apple, int appleSize, int *capacity, int capacitySize) {
  qsort(capacity, capacitySize, sizeof(int), cmp);
  int s = 0;
  for (int i = 0; i < appleSize; ++i) {
    s += apple[i];
  }
  for (int i = 1;; ++i) {
    s -= capacity[i - 1];
    if (s <= 0) {
      return i;
    }
  }
}