long long minNumberOfSeconds(int mountainHeight, int *workerTimes,
                             int workerTimesSize) {
  typedef unsigned long long U;
  typedef __uint128_t W;
  U z = ~(U)0, m = 1ULL << 62, l = 0, r = 0, t = 0, s = 0, x = 0, q = 0;
  int i = 0;
  if (mountainHeight <= 0 || workerTimesSize <= 0)
    return 0;
  for (i = 0; i < workerTimesSize; i++)
    if ((U)workerTimes[i] < m)
      m = (U)workerTimes[i];
  x = (U)mountainHeight;
  q = x * (x + 1ULL) / 2ULL;
  r = (U)(((W)m * (W)q) > (W)z ? z : (W)m * (W)q);
  if (!r)
    r = z;
  while (l < r) {
    t = l + ((r - l) >> 1);
    s = 0;
    for (i = 0; i < workerTimesSize && s < (U)mountainHeight; i++) {
      s += (U)(sqrt((double)t * 2.0 / (double)workerTimes[i] + 0.25) - 0.5);
    }
    if (s >= (U)mountainHeight)
      r = t;
    else
      l = t + 1;
  }
  return (long long)l;
}
