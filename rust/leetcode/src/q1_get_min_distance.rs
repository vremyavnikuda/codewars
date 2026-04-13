impl Solution {
    #[inline(always)]
    pub fn get_min_distance(nums: Vec<i32>, target: i32, start: i32) -> i32 {
        let _n = nums.len() as isize;
        if _n == 0 {
            return 0;
        }
        let _p = nums.as_ptr();
        let mut _c = (start as isize).min(_n - 1);
        _c = _c.max(0);

        let (mut _l, mut _r, mut _d) = (_c, _c, 0isize);
        loop {
            let _a = _l >= 0;
            let _b = _r < _n;
            if !(_a | _b) {
                break;
            }
            unsafe {
                if _a && *_p.offset(_l) == target {
                    return _d as i32;
                }
                if _b && ((_r ^ _l) != 0) && *_p.offset(_r) == target {
                    return _d as i32;
                }
            }
            _d += 1;
            _l -= 1;
            _r += 1;
        }
        _n as i32
    }
}
