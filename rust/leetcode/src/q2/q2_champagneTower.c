static double core(int p, int r, int g) {
  if (g > r) {
    return 0.0;
  }
  double d[102] = {0.0};
  d[0] = (double)p;
  for (int i = 0; i < r; ++i) {
    for (int j = i; j >= 0; --j) {
      double x = d[j] - 1.0;
      if (x > 0.0) {
        double h = x * 0.5;
        d[j] = h;
        d[j + 1] += h;
      } else {
        d[j] = 0.0;
      }
    }
  }
  return d[g] < 1.0 ? d[g] : 1.0;
}

double champagneTower(int poured, int query_row, int query_glass) {
  return core(poured, query_row, query_glass);
}
