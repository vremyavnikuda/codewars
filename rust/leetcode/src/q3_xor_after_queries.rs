impl Solution {
    pub fn xor_after_queries(nums: Vec<i32>, queries: Vec<Vec<i32>>) -> i32 {
        const _0: u64 = 1_000_000_007;
        let mut _1: Vec<u32> = unsafe { std::mem::transmute(nums) };
        let _2 = _1.len();
        let mut _3 = 1usize;
        while _3 * _3 < _2 {
            _3 += 1;
        }
        let mut _4 = vec![Vec::<[u32; 3]>::new(); _3 + 1];
        let mut _5 = vec![0_u64; _3 + 1];
        let mut _6 = vec![1_u32; _3 + 1];
        for _7 in queries {
            let _8 = unsafe { *_7.get_unchecked(0) as usize };
            let _9 = unsafe { *_7.get_unchecked(1) as usize };
            let _a = unsafe { *_7.get_unchecked(2) as usize };
            let _b = unsafe { *_7.get_unchecked(3) as u64 };
            if _b == 1 {
                continue;
            }
            if _a > _3 {
                let mut _c = _8;
                let _p = _1.as_mut_ptr();
                while _c <= _9 {
                    unsafe {
                        let _z = _p.add(_c);
                        *_z = ((*_z as u64 * _b) % _0) as u32;
                    }
                    _c = _c.wrapping_add(_a);
                }
            } else {
                _4[_a].push([_8 as u32, _9 as u32, _b as u32]);
                _5[_a] += ((_9 - _8) / _a + 1) as u64;
                if _b as u32 > _6[_a] {
                    _6[_a] = _b as u32;
                }
            }
        }
        let mut _7 = vec![0_u8; _3 + 1];
        let mut _8 = 1usize;
        let mut _9 = 1usize;
        while _8 <= _3 {
            if !_4[_8].is_empty() && _5[_8] > ((_2 as u64) << 1) + ((_4[_8].len() as u64) << 1) {
                _7[_8] = 1;
                if _6[_8] as usize > _9 {
                    _9 = _6[_8] as usize;
                }
            }
            _8 += 1;
        }
        let mut _b = Vec::<u32>::new();
        if _9 > 1 {
            _b.resize(_9 + 1, 0);
            _b[1] = 1;
            let mut _c = 2usize;
            while _c <= _9 {
                _b[_c] = (_0 - (_0 / _c as u64) * _b[_0 as usize % _c] as u64 % _0) as u32;
                _c += 1;
            }
        }
        let mut _c = vec![0usize; _3 + 1];
        let mut _d = Vec::<u32>::new();
        let mut _e = 1usize;
        while _e <= _3 {
            if _4[_e].is_empty() {
                _e += 1;
                continue;
            }
            if _7[_e] == 0 {
                for _f in &_4[_e] {
                    let _g = _f[0] as usize;
                    let _h = _f[1] as usize;
                    let _i = _f[2] as u64;
                    let mut _j = _g;
                    let _p = _1.as_mut_ptr();
                    while _j <= _h {
                        unsafe {
                            let _z = _p.add(_j);
                            *_z = ((*_z as u64 * _i) % _0) as u32;
                        }
                        _j = _j.wrapping_add(_e);
                    }
                }
                _e += 1;
                continue;
            }
            let mut _f = 0usize;
            let mut _g = 0usize;
            while _f < _e {
                _c[_f] = _g;
                _g += (_2 - _f + _e - 1) / _e + 1;
                _f += 1;
            }
            _c[_e] = _g;
            _d.clear();
            _d.resize(_g, 1);
            for _f in &_4[_e] {
                let _h = _f[0] as usize;
                let _i = _f[1] as usize;
                let _j = _h % _e;
                let _k = _c[_j] + _h / _e;
                let _l = _k + (_i - _h) / _e + 1;
                let _m = _f[2] as u64;
                unsafe {
                    let _x = _d.get_unchecked_mut(_k);
                    *_x = ((*_x as u64 * _m) % _0) as u32;
                    let _y = _d.get_unchecked_mut(_l);
                    *_y = ((*_y as u64 * *_b.get_unchecked(_f[2] as usize) as u64) % _0) as u32;
                }
            }
            let mut _f = 0usize;
            let _p = _1.as_mut_ptr();
            while _f < _e {
                let mut _g = 1_u64;
                let mut _h = _c[_f];
                let mut _i = _f;
                while _i < _2 {
                    unsafe {
                        _g = (_g * *_d.get_unchecked(_h) as u64) % _0;
                        let _z = _p.add(_i);
                        *_z = ((*_z as u64 * _g) % _0) as u32;
                    }
                    _h += 1;
                    _i += _e;
                }
                _f += 1;
            }
            _e += 1;
        }
        let mut _f = 0u32;
        let _p = _1.as_ptr();
        let mut _g = 0usize;
        while _g + 4 <= _2 {
            unsafe {
                _f ^= *_p.add(_g) ^ *_p.add(_g + 1) ^ *_p.add(_g + 2) ^ *_p.add(_g + 3);
            }
            _g += 4;
        }
        while _g < _2 {
            unsafe {
                _f ^= *_p.add(_g);
            }
            _g += 1;
        }
        _f as i32
    }
}
