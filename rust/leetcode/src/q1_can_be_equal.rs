impl Solution {
    pub fn can_be_equal(s1: String, s2: String) -> bool {
        let _0 = s1.as_bytes();
        let _1 = s2.as_bytes();
        let _2 = _0.len();
        if _2 != _1.len() {
            return false;
        }
        let mut _3 = [0_i32; 52];
        let mut _4: usize = 0;
        while _4 < _2 {
            unsafe {
                let _5 = (*_0.get_unchecked(_4) - b'a') as usize;
                let _6 = (*_1.get_unchecked(_4) - b'a') as usize;
                let _7 = (_4 & 1) * 26;
                *_3.get_unchecked_mut(_7 + _5) += 1;
                *_3.get_unchecked_mut(_7 + _6) -= 1;
            }
            _4 += 1;
        }
        let mut _8: usize = 0;
        while _8 < 52 {
            if unsafe { *_3.get_unchecked(_8) } != 0 {
                return false;
            }
            _8 += 1;
        }
        true
    }
}
