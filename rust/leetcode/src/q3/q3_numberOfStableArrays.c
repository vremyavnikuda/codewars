#include <stdint.h>
#include <stdlib.h>

int numberOfStableArrays(int zero, int one, int limit) {
  enum { _M = 1000000007 };
  int _u = zero, _v = one, _w = limit;
  size_t _p = ((size_t)((_w < _u) ? _w : _u) + 2u) * ((size_t)_v + 1u);
  size_t _q = ((size_t)((_w < _v) ? _w : _v) + 2u) * ((size_t)_u + 1u);
  int _s = (_q < _p);
  int _a = _s ? _v : _u, _b = _s ? _u : _v;
  size_t _W = (size_t)_b + 1u, _R = (size_t)((_w < _a) ? _w : _a) + 2u, _T = _W * _R;
  int *_m = (int *)calloc(_T * 2u, sizeof(int));
  if (!_m) return 0;
  int *_x = _m, *_y = _m + _T;

  for (size_t _i = 0; _i <= (size_t)_a; ++_i) {
    size_t _r = (_i % _R) * _W, _pr = ((_i + _R - 1u) % _R) * _W;
    int *_xr = _x + _r, *_yr = _y + _r, *_xp = _x + _pr, *_yp = _y + _pr;
    if (_i == 0u) {
      _xr[0] = 0;
      _yr[0] = 1;
      for (size_t _j = 1; _j <= (size_t)_b; ++_j) {
        _xr[_j] = 0;
        _yr[_j] = (_j <= (size_t)_w);
      }
      continue;
    }
    _xr[0] = (_i <= (size_t)_w);
    _yr[0] = 0;
    int *_yo = (_i > (size_t)_w) ? (_y + (((_i - (size_t)_w - 1u) % _R) * _W)) : 0;
    for (size_t _j = 1; _j <= (size_t)_b; ++_j) {
      int64_t _t = (int64_t)_xp[_j] + _yp[_j] - (_yo ? _yo[_j] : 0);
      _t += (_t < 0) * _M;
      _t -= (_t >= _M) * _M;
      _xr[_j] = (int)_t;

      int64_t _z = (int64_t)_xr[_j - 1u] + _yr[_j - 1u] - ((_j > (size_t)_w) ? _xr[_j - (size_t)_w - 1u] : 0);
      _z += (_z < 0) * _M;
      _z -= (_z >= _M) * _M;
      _yr[_j] = (int)_z;
    }
  }

  size_t _e = (((size_t)_a % _R) * _W) + (size_t)_b;
  int _ans = _x[_e] + _y[_e];
  _ans -= (_ans >= _M) * _M;
  free(_m);
  return _ans;
}
