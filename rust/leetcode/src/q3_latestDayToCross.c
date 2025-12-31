#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
  int x;
  int y;
} Point;

typedef struct {
  Point *data;
  int front;
  int rear;
  int capacity;
} Queue;

void initQueue(Queue *q, int capacity) {
  q->data = (Point *)malloc(capacity * sizeof(Point));
  q->front = 0;
  q->rear = 0;
  q->capacity = capacity;
}

void freeQueue(Queue *q) { free(q->data); }

void enqueue(Queue *q, int x, int y) {
  q->data[q->rear].x = x;
  q->data[q->rear].y = y;
  q->rear++;
}

Point dequeue(Queue *q) { return q->data[q->front++]; }

bool isEmpty(Queue *q) { return q->front == q->rear; }

bool check(int row, int col, int **cells, int k) {
  int **g = (int **)malloc(row * sizeof(int *));
  for (int i = 0; i < row; ++i) {
    g[i] = (int *)calloc(col, sizeof(int));
  }
  for (int i = 0; i < k; ++i) {
    g[cells[i][0] - 1][cells[i][1] - 1] = 1;
  }
  Queue q;
  initQueue(&q, row * col);
  for (int j = 0; j < col; ++j) {
    if (g[0][j] == 0) {
      enqueue(&q, 0, j);
      g[0][j] = 1;
    }
  }
  int dirs[5] = {0, 1, 0, -1, 0};
  bool result = false;
  while (!isEmpty(&q)) {
    Point p = dequeue(&q);
    int x = p.x;
    int y = p.y;
    if (x == row - 1) {
      result = true;
      break;
    }
    for (int i = 0; i < 4; ++i) {
      int nx = x + dirs[i];
      int ny = y + dirs[i + 1];
      if (nx >= 0 && nx < row && ny >= 0 && ny < col && g[nx][ny] == 0) {
        enqueue(&q, nx, ny);
        g[nx][ny] = 1;
      }
    }
  }
  freeQueue(&q);
  for (int i = 0; i < row; ++i) {
    free(g[i]);
  }
  free(g);
  return result;
}

int latestDayToCross(int row, int col, int **cells, int cellsSize,
                     int *cellsColSize) {
  int l = 1;
  int r = cellsSize;
  while (l < r) {
    int mid = (l + r + 1) >> 1;
    if (check(row, col, cells, mid)) {
      l = mid;
    } else {
      r = mid - 1;
    }
  }
  return l;
}

int main() {
  int r1_0[] = {1, 2};
  int r1_1[] = {2, 1};
  int r1_2[] = {3, 3};
  int r1_3[] = {2, 2};
  int r1_4[] = {1, 1};
  int r1_5[] = {1, 3};
  int r1_6[] = {2, 3};
  int r1_7[] = {3, 2};
  int r1_8[] = {3, 1};
  int *c1[] = {r1_0, r1_1, r1_2, r1_3, r1_4, r1_5, r1_6, r1_7, r1_8};
  int cs1[] = {2, 2, 2, 2, 2, 2, 2, 2, 2};
  printf("Test 1: %d\n", latestDayToCross(3, 3, c1, 9, cs1));
  return 0;
}
