impl Solution {
    #[inline(always)]
    pub fn min_jumps(arr: Vec<i32>) -> i32 {
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
            #[inline(always)]
            fn write_u32(&mut self, i: u32) {
                self.0 = i as u64;
            }
        }

        type _S = std::hash::BuildHasherDefault<_H>;
        let n = arr.len();
        if n < 2 {
            return 0;
        }
        let z = (n - 1) as u32;
        if unsafe { *arr.get_unchecked(0) } == unsafe { *arr.get_unchecked(z as usize) } {
            return 1;
        }

        let u = u32::MAX;
        let mut m: std::collections::HashMap<i32, u32, _S> =
            std::collections::HashMap::with_capacity_and_hasher(n, _S::default());
        let mut nx = vec![u; n];
        use std::collections::hash_map::Entry::{Occupied, Vacant};
        let mut i = n as u32;
        while i != 0 {
            i -= 1;
            let k = unsafe { *arr.get_unchecked(i as usize) };
            match m.entry(k) {
                Vacant(e) => {
                    e.insert(i);
                }
                Occupied(mut e) => {
                    unsafe {
                        *nx.get_unchecked_mut(i as usize) = *e.get();
                    }
                    *e.get_mut() = i;
                }
            }
        }

        let mut q = vec![0u32; n];
        let mut v = vec![0u8; n];
        v[0] = 1;
        let (mut h, mut t, mut r, mut d) = (0usize, 1usize, 1usize, 0i32);

        while h < t {
            while h < r {
                let p = unsafe { *q.get_unchecked(h) };
                h += 1;
                if p == z {
                    return d;
                }

                let x = unsafe { *arr.get_unchecked(p as usize) };
                if let Some(s) = m.get_mut(&x) {
                    let mut j = *s;
                    if j != u {
                        *s = u;
                        while j != u {
                            if j == z {
                                return d + 1;
                            }
                            let w = j as usize;
                            if unsafe { *v.get_unchecked(w) } == 0 {
                                unsafe {
                                    *v.get_unchecked_mut(w) = 1;
                                    *q.get_unchecked_mut(t) = j;
                                }
                                t += 1;
                            }
                            j = unsafe { *nx.get_unchecked(w) };
                        }
                    }
                }

                if p != 0 {
                    let j = p - 1;
                    let w = j as usize;
                    if unsafe { *v.get_unchecked(w) } == 0 {
                        unsafe {
                            *v.get_unchecked_mut(w) = 1;
                            *q.get_unchecked_mut(t) = j;
                        }
                        t += 1;
                    }
                }

                let j = p + 1;
                if j <= z {
                    if j == z {
                        return d + 1;
                    }
                    let w = j as usize;
                    if unsafe { *v.get_unchecked(w) } == 0 {
                        unsafe {
                            *v.get_unchecked_mut(w) = 1;
                            *q.get_unchecked_mut(t) = j;
                        }
                        t += 1;
                    }
                }
            }
            r = t;
            d += 1;
        }
        0
    }
}
