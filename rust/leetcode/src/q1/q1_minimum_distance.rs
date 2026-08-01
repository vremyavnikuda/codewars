impl Solution {
    pub fn minimum_distance(nums: Vec<i32>) -> i32 {
        let _n = nums.len();
        if _n < 3 {
            return -1;
        }
        let mut _m: Vec<u32> = (0.._n as u32).collect();
        let _p = nums.as_ptr();
        _m.sort_unstable_by(|_l, _r| unsafe {
            let _x = *_p.add(*_l as usize);
            let _y = *_p.add(*_r as usize);
            if _x == _y {
                _l.cmp(_r)
            } else {
                _x.cmp(&_y)
            }
        });
        let mut _a = 0usize;
        let mut _z: i32 = 0x3f3f3f3f;
        while _a < _n {
            let _v = unsafe { *_p.add(*_m.get_unchecked(_a) as usize) };
            let mut _b = _a + 1;
            while _b < _n && unsafe { *_p.add(*_m.get_unchecked(_b) as usize) } == _v {
                _b += 1;
            }
            if _b - _a > 2 {
                let mut _c = _a + 2;
                while _c < _b {
                    let _d = unsafe {
                        ((*_m.get_unchecked(_c) as i32) - (*_m.get_unchecked(_c - 2) as i32)) << 1
                    };
                    if _d < _z {
                        _z = _d;
                    }
                    _c += 1;
                }
            }
            _a = _b;
        }
        if _z == 0x3f3f3f3f {
            -1
        } else {
            _z
        }
    }
}
