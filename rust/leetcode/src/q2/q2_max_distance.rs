impl Solution {
    #[inline(always)]
    pub fn max_distance(nums1: Vec<i32>, nums2: Vec<i32>) -> i32 {
        let (_n1, _n2) = (nums1.len(), nums2.len());
        if (_n1 | _n2) == 0 {
            return 0;
        }

        let (mut _i, mut _j, mut _r) = (0usize, 0usize, 0usize);
        unsafe {
            while _i < _n1 && _j < _n2 {
                let (_a, _b) = (*nums1.get_unchecked(_i), *nums2.get_unchecked(_j));
                if _a <= _b {
                    _r = _r.max(_j.wrapping_sub(_i));
                    _j += 1;
                } else {
                    _i += 1;
                    _j = _j.max(_i);
                }
            }
        }
        _r as i32
    }
}
