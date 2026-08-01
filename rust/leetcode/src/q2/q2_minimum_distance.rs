impl Solution {
    pub fn minimum_distance(nums: Vec<i32>) -> i32 {
        #[derive(Default)]
        struct _H(u64);
        impl std::hash::Hasher for _H {
            #[inline(always)]
            fn finish(&self) -> u64 {
                self.0
            }
            #[inline(always)]
            fn write(&mut self, b: &[u8]) {
                let mut z = 0u64;
                let mut i = 0usize;
                while i < b.len() {
                    z |= (b[i] as u64) << ((i & 7) << 3);
                    i += 1;
                }
                self.0 = z;
            }
            #[inline(always)]
            fn write_i32(&mut self, i: i32) {
                self.0 = (i as u32) as u64;
            }
        }

        type _S = std::hash::BuildHasherDefault<_H>;
        let mut _m: std::collections::HashMap<i32, u64, _S> =
            std::collections::HashMap::with_capacity_and_hasher(nums.len(), _S::default());
        let mut _a = 0x3f3f3f3f_i32;
        let mut _i = 0usize;
        while _i < nums.len() {
            let _x = unsafe { *nums.get_unchecked(_i) };
            let _p = _i as u32;
            use std::collections::hash_map::Entry::{Occupied, Vacant};
            match _m.entry(_x) {
                Vacant(_e) => {
                    _e.insert(((u32::MAX as u64) << 32) | (_p as u64));
                }
                Occupied(mut _e) => {
                    let _z = *_e.get();
                    let _q = (_z >> 32) as u32;
                    if _q != u32::MAX {
                        let _t = ((_p.wrapping_sub(_q)) as i32) << 1;
                        if _t < _a {
                            _a = _t;
                        }
                    }
                    *_e.get_mut() = (((_z as u32) as u64) << 32) | (_p as u64);
                }
            }
            _i += 1;
        }
        if _a == 0x3f3f3f3f { -1 } else { _a }
    }
}
