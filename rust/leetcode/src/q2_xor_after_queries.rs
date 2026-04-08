impl Solution {
    pub fn xor_after_queries(nums: Vec<i32>, queries: Vec<Vec<i32>>) -> i32 {
        const _0: u64 = 1_000_000_007;
        let mut _1 = nums;
        for _2 in queries {
            let _3 = _2[0] as usize;
            let _4 = _2[1] as usize;
            let _5 = _2[2] as usize;
            let _6 = _2[3] as u64;
            if _6 == 1 {
                continue;
            }
            if _5 == 1 {
                for _7 in &mut _1[_3..=_4] {
                    *_7 = (((*_7 as u64) * _6) % _0) as i32;
                }
            } else {
                let mut _7 = _3;
                while _7 <= _4 {
                    _1[_7] = (((_1[_7] as u64) * _6) % _0) as i32;
                    _7 += _5;
                }
            }
        }
        let mut _8 = 0_i32;
        for _9 in _1 {
            _8 ^= _9;
        }
        _8
    }
}
