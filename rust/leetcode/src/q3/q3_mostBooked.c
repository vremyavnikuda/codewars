#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  long long t;
  int r;
} P;

int cmp_m(const void *a, const void *b) {
  int *x = *(int **)a;
  int *y = *(int **)b;
  return x[0] - y[0];
}

void sw_p(P *a, P *b) {
  P t = *a;
  *a = *b;
  *b = t;
}

void sw_i(int *a, int *b) {
  int t = *a;
  *a = *b;
  *b = t;
}

void h_up_p(P *h, int i) {
  while (i > 0) {
    int p = (i - 1) / 2;
    if (h[i].t < h[p].t || (h[i].t == h[p].t && h[i].r < h[p].r)) {
      sw_p(&h[i], &h[p]);
      i = p;
    } else
      break;
  }
}

void h_down_p(P *h, int s, int i) {
  while (1) {
    int l = 2 * i + 1;
    int r = 2 * i + 2;
    int m = i;

    if (l < s && (h[l].t < h[m].t || (h[l].t == h[m].t && h[l].r < h[m].r)))
      m = l;
    if (r < s && (h[r].t < h[m].t || (h[r].t == h[m].t && h[r].r < h[m].r)))
      m = r;

    if (m != i) {
      sw_p(&h[i], &h[m]);
      i = m;
    } else
      break;
  }
}

void h_up_i(int *h, int i) {
  while (i > 0) {
    int p = (i - 1) / 2;
    if (h[i] < h[p]) {
      sw_i(&h[i], &h[p]);
      i = p;
    } else
      break;
  }
}

void h_down_i(int *h, int s, int i) {
  while (1) {
    int l = 2 * i + 1;
    int r = 2 * i + 2;
    int m = i;

    if (l < s && h[l] < h[m])
      m = l;
    if (r < s && h[r] < h[m])
      m = r;

    if (m != i) {
      sw_i(&h[i], &h[m]);
      i = m;
    } else
      break;
  }
}

int mostBooked(int n, int **meetings, int meetingsSize, int *meetingsColSize) {
  qsort(meetings, meetingsSize, sizeof(int *), cmp_m);

  P *busy = (P *)malloc(n * sizeof(P));
  int bs = 0;

  int *idle = (int *)malloc(n * sizeof(int));
  int is = 0;

  for (int i = 0; i < n; ++i) {
    idle[is++] = i;
    h_up_i(idle, is - 1);
  }

  int *cnt = (int *)calloc(n, sizeof(int));

  for (int k = 0; k < meetingsSize; ++k) {
    int s = meetings[k][0];
    int e = meetings[k][1];

    while (bs > 0 && busy[0].t <= s) {
      idle[is++] = busy[0].r;
      h_up_i(idle, is - 1);

      busy[0] = busy[--bs];
      if (bs > 0)
        h_down_p(busy, bs, 0);
    }

    int i;
    if (is > 0) {
      i = idle[0];
      idle[0] = idle[--is];
      if (is > 0)
        h_down_i(idle, is, 0);

      busy[bs++] = (P){e, i};
      h_up_p(busy, bs - 1);
    } else {
      P x = busy[0];
      busy[0] = busy[--bs];
      if (bs > 0)
        h_down_p(busy, bs, 0);

      i = x.r;
      busy[bs++] = (P){x.t + e - s, i};
      h_up_p(busy, bs - 1);
    }

    ++cnt[i];
  }

  int ans = 0;
  for (int i = 1; i < n; ++i) {
    if (cnt[i] > cnt[ans]) {
      ans = i;
    }
  }

  free(busy);
  free(idle);
  free(cnt);

  return ans;
}

int main() {
  int m1_data[][2] = {{0, 10}, {1, 5}, {2, 7}, {3, 4}};
  int *m1[4];
  for (int i = 0; i < 4; i++)
    m1[i] = m1_data[i];
  int cs1[4] = {2, 2, 2, 2};

  printf("%d\n", mostBooked(2, m1, 4, cs1));

  return 0;
}
