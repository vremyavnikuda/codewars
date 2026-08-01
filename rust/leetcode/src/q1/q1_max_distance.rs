impl Solution {
    #[inline(always)]
    pub fn max_distance(colors: Vec<i32>) -> i32 {
        let _n = colors.len();
        if _n < 2 {
            return 0;
        }

        let _p = colors.as_ptr();
        let (_h, _t) = unsafe { (*_p, *_p.add(_n - 1)) };
        let mut _r = 0usize;

        let mut _i = _n - 1;
        while _i > 0 {
            if unsafe { *_p.add(_i) ^ _h } != 0 {
                _r = _i;
                break;
            }
            _i = _i.wrapping_sub(1);
        }

        let mut _j = 0usize;
        while _j + 1 < _n {
            if unsafe { *_p.add(_j) ^ _t } != 0 {
                let _d = (_n - 1).wrapping_sub(_j);
                if _d > _r {
                    _r = _d;
                }
                break;
            }
            _j += 1;
        }

        _r as i32
    }
}
