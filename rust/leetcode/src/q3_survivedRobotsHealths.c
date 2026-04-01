#include <stdlib.h>

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* survivedRobotsHealths(int* positions, int positionsSize, int* healths, int healthsSize, char* directions, int* returnSize) {
    (void)healthsSize;
    int _0 = positionsSize;
    if (_0 <= 0) {
        *returnSize = 0;
        return NULL;
    }
    int* _1 = (int*)malloc((size_t)_0 * sizeof(int));
    if (!_1) {
        *returnSize = 0;
        return NULL;
    }
    for (int _2 = 0; _2 < _0; ++_2) _1[_2] = _2;
    {
        int _3[96], _4[96], _5 = 0;
        _3[_5] = 0;
        _4[_5++] = _0 - 1;
        while (_5) {
            int _6 = _3[--_5], _7 = _4[_5];
            while (_7 - _6 > 20) {
                int _8 = _6, _9 = _7;
                int _a = positions[_1[(_6 + _7) >> 1]];
                do {
                    while (positions[_1[_8]] < _a) ++_8;
                    while (positions[_1[_9]] > _a) --_9;
                    if (_8 <= _9) {
                        int _b = _1[_8];
                        _1[_8++] = _1[_9];
                        _1[_9--] = _b;
                    }
                } while (_8 <= _9);
                if (_9 - _6 < _7 - _8) {
                    if (_8 < _7) {
                        _3[_5] = _8;
                        _4[_5++] = _7;
                    }
                    _7 = _9;
                } else {
                    if (_6 < _9) {
                        _3[_5] = _6;
                        _4[_5++] = _9;
                    }
                    _6 = _8;
                }
            }
            for (int _c = _6 + 1; _c <= _7; ++_c) {
                int _d = _1[_c], _e = positions[_d], _f = _c - 1;
                while (_f >= _6 && positions[_1[_f]] > _e) {
                    _1[_f + 1] = _1[_f];
                    --_f;
                }
                _1[_f + 1] = _d;
            }
        }
    }
    {
        int _g = 0;
        for (int _h = 0; _h < _0; ++_h) {
            int _i = _1[_h];
            if (directions[_i] == 'R') {
                _1[_g++] = _i;
                continue;
            }
            while (_g && healths[_i] > 0) {
                int _j = _1[_g - 1];
                int _k = healths[_j], _l = healths[_i];
                if (_k > _l) {
                    healths[_j] = _k - 1;
                    healths[_i] = 0;
                } else if (_k < _l) {
                    healths[_i] = _l - 1;
                    healths[_j] = 0;
                    --_g;
                } else {
                    healths[_i] = 0;
                    healths[_j] = 0;
                    --_g;
                    break;
                }
            }
        }
    }
    int _m = 0;
    for (int _n = 0; _n < _0; ++_n) _m += (healths[_n] > 0);
    *returnSize = _m;
    int* _o = _m ? (int*)malloc((size_t)_m * sizeof(int)) : NULL;
    for (int _p = 0, _q = 0; _p < _0; ++_p) {
        if (healths[_p] > 0) _o[_q++] = healths[_p];
    }
    free(_1);
    return _o;
}
