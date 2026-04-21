use std::collections::HashMap;
use std::hash::{BuildHasherDefault, Hasher};

#[derive(Default)]
struct _Z(u64);

impl Hasher for _Z {
    #[inline(always)]
    fn finish(&self) -> u64 {
        self.0
    }

    #[inline(always)]
    fn write(&mut self, _b: &[u8]) {
        let mut _x = 0u64;
        let mut _i = 0usize;
        while _i < _b.len() {
            _x = _x.rotate_left(7) ^ _b[_i] as u64;
            _i += 1;
        }
        self.0 = _x;
    }

    #[inline(always)]
    fn write_u64(&mut self, _i: u64) {
        self.0 = _i;
    }
}

#[inline(always)]
fn _f(mut _x: usize, _p: &mut [usize]) -> usize {
    let mut _r = _x;
    while unsafe { *_p.get_unchecked(_r) } != _r {
        _r = unsafe { *_p.get_unchecked(_r) };
    }
    while unsafe { *_p.get_unchecked(_x) } != _r {
        let _n = unsafe { *_p.get_unchecked(_x) };
        unsafe { *_p.get_unchecked_mut(_x) = _r };
        _x = _n;
    }
    _r
}

impl Solution {
    #[inline(always)]
    pub fn minimum_hamming_distance(
        source: Vec<i32>,
        target: Vec<i32>,
        allowed_swaps: Vec<Vec<i32>>,
    ) -> i32 {
        type _M = HashMap<u64, i32, BuildHasherDefault<_Z>>;

        let _n = source.len();
        let mut _p: Vec<usize> = (0.._n).collect();
        let mut _rk = vec![0u8; _n];

        let mut _i = 0usize;
        while _i < allowed_swaps.len() {
            let _e = unsafe { allowed_swaps.get_unchecked(_i) };
            let mut _a = unsafe { *_e.get_unchecked(0) } as usize;
            let mut _b = unsafe { *_e.get_unchecked(1) } as usize;

            _a = _f(_a, &mut _p);
            _b = _f(_b, &mut _p);

            if _a != _b {
                if unsafe { *_rk.get_unchecked(_a) } < unsafe { *_rk.get_unchecked(_b) } {
                    std::mem::swap(&mut _a, &mut _b);
                }
                unsafe { *_p.get_unchecked_mut(_b) = _a };
                if unsafe { *_rk.get_unchecked(_a) } == unsafe { *_rk.get_unchecked(_b) } {
                    unsafe {
                        let _q = *_rk.get_unchecked(_a);
                        *_rk.get_unchecked_mut(_a) = _q.wrapping_add(1);
                    };
                }
            }
            _i += 1;
        }

        let mut _cnt: _M =
            HashMap::with_capacity_and_hasher(_n.wrapping_mul(2).wrapping_add(1), Default::default());

        let _sp = source.as_ptr();
        let _tp = target.as_ptr();

        _i = 0;
        while _i < _n {
            let _r = _f(_i, &mut _p);
            let _v = unsafe { *_sp.add(_i) };
            let _k = ((_r as u64) << 32) | (_v as u32 as u64);
            *_cnt.entry(_k).or_insert(0) += 1;
            _i += 1;
        }

        let mut _ans = 0i32;
        _i = 0;
        while _i < _n {
            let _r = _f(_i, &mut _p);
            let _v = unsafe { *_tp.add(_i) };
            let _k = ((_r as u64) << 32) | (_v as u32 as u64);
            let _z = _cnt.entry(_k).or_insert(0);
            * _z -= 1;
            _ans += ((*_z >> 31) & 1) as i32;
            _i += 1;
        }

        _ans
    }
}
