pub struct Solution;

impl Solution {
    #[inline(always)]
    pub fn has_all_codes(s: String, k: i32) -> bool {
        let (_0, _1) = (s.as_bytes(), k as usize);
        if _1 == 0 {
            return true;
        }
        let _2 = _0.len();
        let _3 = match 1usize.checked_shl(_1 as u32) {
            Some(v) => v,
            None => return false,
        };
        let _4 = _2.wrapping_sub(_1).wrapping_add(1);
        if _2 < _1 || _4 < _3 {
            return false;
        }
        let mut _5 = vec![0u64; (_3 + 63) >> 6];
        let mut _6 = 0usize;
        let mut _7 = 0usize;
        let _8 = _3 - 1;
        let mut _9 = 0usize;
        while _9 < _2 {
            _7 = ((_7 << 1) & _8) | ((_0[_9] & 1) as usize);
            if _9 + 1 >= _1 {
                let _a = _7 >> 6;
                let _b = 1u64 << (_7 & 63);
                let _c = _5[_a];
                if _c & _b == 0 {
                    _5[_a] = _c | _b;
                    _6 += 1;
                    if _6 == _3 {
                        return true;
                    }
                }
            }
            _9 += 1;
        }
        false
    }
}
