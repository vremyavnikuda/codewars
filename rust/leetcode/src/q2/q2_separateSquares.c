static int **sq;
static int sz;
static double s;

int chk(double y) {
  double t = 0.0;
  int i;
  for (i = 0; i < sz; ++i) {
    int yi = sq[i][1], l = sq[i][2];
    if (yi < y) {
      double d = y - yi;
      t += l * (d < l ? d : l);
    }
  }
  return t >= s * 0.5;
}

double separateSquares(int **squares, int squaresSize, int *squaresColSize) {
  sq = squares;
  sz = squaresSize;
  s = 0.0;
  double l = 0.0, r = 0.0, m;
  int i;
  for (i = 0; i < sz; ++i) {
    int si = squares[i][2];
    s += (double)si * si;
    double t = squares[i][1] + si;
    if (t > r)
      r = t;
  }
  while (r - l > 1e-5) {
    m = (l + r) * 0.5;
    if (chk(m))
      r = m;
    else
      l = m;
  }
  return r;
}
