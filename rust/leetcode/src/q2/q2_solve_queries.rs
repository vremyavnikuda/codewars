impl Solution {
    #[inline(always)]
    pub fn solve_queries(nums: Vec<i32>, queries: Vec<i32>) -> Vec<i32> {
        #[derive(Default)]
        struct _H(u64);
        impl std::hash::Hasher for _H {
            #[inline(always)]
            fn finish(&self) -> u64 {
                self.0
            }
            #[inline(always)]
            fn write(&mut self, b: &[u8]) {
                let mut _z = 0u64;
                let mut _i = 0usize;
                while _i < b.len() {
                    _z |= (b[_i] as u64) << ((_i & 7) << 3);
                    _i += 1;
                }
                self.0 = _z;
            }
            #[inline(always)]
            fn write_i32(&mut self, i: i32) {
                self.0 = (i as u32) as u64;
            }
        }

        type _S = std::hash::BuildHasherDefault<_H>;

        let _0 = nums.len();
        let _1 = queries.len();
        if _0 == 0 {
            return vec![-1; _1];
        }
        let _2 = (_0 as i32).max(0);
        let _3 = _0 << 1;

        let mut _4 = vec![_2; _0];
        let mut _5: std::collections::HashMap<i32, u32, _S> =
            std::collections::HashMap::with_capacity_and_hasher(_0 << 1, _S::default());

        let mut _6 = 0usize;
        while _6 < _3 {
            let _7 = _6 - ((_6 >= _0) as usize) * _0;
            let _8 = unsafe { *nums.get_unchecked(_7) };
            let _9 = _6 as u32;
            if let Some(&_a) = _5.get(&_8) {
                let _b = _9.wrapping_sub(_a) as i32;
                let _c = unsafe { _4.get_unchecked_mut(_7) };
                if _b < *_c {
                    *_c = _b;
                }
            }
            _5.insert(_8, _9);
            _6 += 1;
        }

        _5.clear();
        _6 = _3;
        while _6 > 0 {
            _6 -= 1;
            let _7 = _6 - ((_6 >= _0) as usize) * _0;
            let _8 = unsafe { *nums.get_unchecked(_7) };
            let _9 = _6 as u32;
            if let Some(&_a) = _5.get(&_8) {
                let _b = _a.wrapping_sub(_9) as i32;
                let _c = unsafe { _4.get_unchecked_mut(_7) };
                if _b < *_c {
                    *_c = _b;
                }
            }
            _5.insert(_8, _9);
        }

        let mut _r = Vec::with_capacity(_1);
        let mut _i = 0usize;
        while _i < _1 {
            let _q = unsafe { *queries.get_unchecked(_i) } as usize;
            let _d = unsafe { *_4.get_unchecked(_q) };
            _r.push(if _d >= _2 { -1 } else { _d });
            _i += 1;
        }
        _r
    }
}
