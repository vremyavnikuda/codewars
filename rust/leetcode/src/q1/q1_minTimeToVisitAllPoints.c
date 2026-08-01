int minTimeToVisitAllPoints(int **points, int pointsSize, int *pointsColSize) {
  int a = 0, i, dx, dy;
  for (i = 1; i < pointsSize; ++i) {
    dx = points[i][0] - points[i - 1][0];
    dy = points[i][1] - points[i - 1][1];
    if (dx < 0)
      dx = -dx;
    if (dy < 0)
      dy = -dy;
    a += dx > dy ? dx : dy;
  }
  return a;
}
