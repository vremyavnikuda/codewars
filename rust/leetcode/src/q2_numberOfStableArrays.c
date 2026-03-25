#include <stdint.h>
#include <stdlib.h>

int numberOfStableArrays(int zero, int one, int limit) {
  enum { _M = 1000000007 };
  size_t _a = (size_t)one + 1u, _b = (size_t)zero + 1u, _c = _a * _b;
  int *_x = (int *)calloc(_c, sizeof(int)), *_y = (int *)calloc(_c, sizeof(int));
  if (!_x || !_y) {
    free(_x);
    free(_y);
    return 0;
  }

  _y[0] = 1;
  for (size_t _j = 1; _j < _a; ++_j) _y[_j] = (_j <= (size_t)limit);
  for (size_t _i = 1; _i < _b; ++_i) _x[_i * _a] = (_i <= (size_t)limit);

  for (size_t _i = 1; _i < _b; ++_i) {
    size_t _r = _i * _a, _p = _r - _a;
    int _k = (_i > (size_t)limit);
    size_t _q = _k ? (_r - ((size_t)limit + 1u) * _a) : 0u;
    for (size_t _j = 1; _j < _a; ++_j) {
      int64_t _u = (int64_t)_x[_p + _j] + _y[_p + _j] - (_k ? _y[_q + _j] : 0);
      _u += (_u < 0) * _M;
      _u -= (_u >= _M) * _M;
      _x[_r + _j] = (int)_u;

      int _t = (_j > (size_t)limit);
      int64_t _v =
          (int64_t)_x[_r + _j - 1u] + _y[_r + _j - 1u] - (_t ? _x[_r + _j - (size_t)limit - 1u] : 0);
      _v += (_v < 0) * _M;
      _v -= (_v >= _M) * _M;
      _y[_r + _j] = (int)_v;
    }
  }

  int _z = _x[_c - 1u] + _y[_c - 1u];
  _z -= (_z >= _M) * _M;
  free(_x);
  free(_y);
  return _z;
}
