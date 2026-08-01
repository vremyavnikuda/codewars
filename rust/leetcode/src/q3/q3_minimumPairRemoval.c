#include <stdlib.h>

typedef struct {
    long long sum;
    int idx;
} HeapNode;

typedef struct {
    HeapNode* data;
    int size;
} MinHeap;

static int heap_less(const HeapNode* a, const HeapNode* b) {
    if (a->sum != b->sum) return a->sum < b->sum;
    return a->idx < b->idx;
}

static void heap_push(MinHeap* h, HeapNode node) {
    int i = h->size++;
    h->data[i] = node;
    while (i > 0) {
        int p = (i - 1) >> 1;
        if (heap_less(&h->data[p], &h->data[i])) break;
        HeapNode tmp = h->data[p];
        h->data[p] = h->data[i];
        h->data[i] = tmp;
        i = p;
    }
}

static HeapNode heap_pop(MinHeap* h) {
    HeapNode res = h->data[0];
    h->size--;
    if (h->size > 0) {
        h->data[0] = h->data[h->size];
        int i = 0;
        for (;;) {
            int l = i * 2 + 1;
            int r = l + 1;
            int m = i;
            if (l < h->size && heap_less(&h->data[l], &h->data[m])) m = l;
            if (r < h->size && heap_less(&h->data[r], &h->data[m])) m = r;
            if (m == i) break;
            HeapNode tmp = h->data[i];
            h->data[i] = h->data[m];
            h->data[m] = tmp;
            i = m;
        }
    }
    return res;
}

int minimumPairRemoval(int* nums, int numsSize) {
    if (numsSize <= 1) return 0;

    int n = numsSize;
    long long* arr = (long long*)malloc((size_t)n * sizeof(long long));
    int* prev = (int*)malloc((size_t)n * sizeof(int));
    int* next = (int*)malloc((size_t)n * sizeof(int));
    unsigned char* alive = (unsigned char*)malloc((size_t)n);

    for (int i = 0; i < n; ++i) {
        arr[i] = (long long)nums[i];
        prev[i] = i - 1;
        next[i] = (i + 1 < n) ? i + 1 : -1;
        alive[i] = 1;
    }

    int inv = 0;
    for (int i = 0; i + 1 < n; ++i) {
        if (arr[i] > arr[i + 1]) inv++;
    }

    int heap_cap = n * 4 + 8;
    MinHeap heap;
    heap.data = (HeapNode*)malloc((size_t)heap_cap * sizeof(HeapNode));
    heap.size = 0;

    for (int i = 0; i + 1 < n; ++i) {
        HeapNode node;
        node.sum = arr[i] + arr[i + 1];
        node.idx = i;
        heap_push(&heap, node);
    }

    int ans = 0;
    while (inv > 0) {
        HeapNode node;
        do {
            node = heap_pop(&heap);
        } while (!alive[node.idx] || next[node.idx] == -1 ||
                 node.sum != arr[node.idx] + arr[next[node.idx]]);

        int i = node.idx;
        int j = next[i];
        long long s = node.sum;

        int h = prev[i];
        int k = next[j];

        if (h != -1 && arr[h] > arr[i]) inv--;
        if (arr[i] > arr[j]) inv--;
        if (k != -1 && arr[j] > arr[k]) inv--;

        arr[i] = s;
        alive[j] = 0;
        next[i] = k;
        if (k != -1) prev[k] = i;

        if (h != -1 && arr[h] > arr[i]) inv++;
        if (k != -1 && arr[i] > arr[k]) inv++;

        if (h != -1) {
            HeapNode hn;
            hn.sum = arr[h] + arr[i];
            hn.idx = h;
            heap_push(&heap, hn);
        }
        if (k != -1) {
            HeapNode in;
            in.sum = arr[i] + arr[k];
            in.idx = i;
            heap_push(&heap, in);
        }

        ans++;
    }

    free(arr);
    free(prev);
    free(next);
    free(alive);
    free(heap.data);
    return ans;
}
