impl Solution {
    #[inline(always)]
    pub fn closest_target(words: Vec<String>, target: String, start_index: i32) -> i32 {
        let n0 = words.len();
        let mut r0 = n0 as i32;
        let p0 = words.as_ptr();
        let t0 = target.as_bytes();
        let l0 = t0.len();
        let s0 = start_index as isize;
        let mut i0: isize = 0;

        while i0 < n0 as isize {
            unsafe {
                let w0 = &*p0.offset(i0);
                let b0 = w0.as_bytes();
                if b0.len() == l0 {
                    let mut k0 = 0usize;
                    while k0 < l0 {
                        if *b0.get_unchecked(k0) != *t0.get_unchecked(k0) {
                            break;
                        }
                        k0 += 1;
                    }
                    if k0 == l0 {
                        let z0 = i0 - s0;
                        let m0 = z0 >> ((isize::BITS - 1) as usize);
                        let d0 = ((z0 ^ m0) - m0) as i32;
                        let d1 = n0 as i32 - d0;
                        let x0 = d0 ^ ((d0 ^ d1) & -((d0 > d1) as i32));
                        r0 = r0 ^ ((r0 ^ x0) & -((r0 > x0) as i32));
                        if r0 == 0 {
                            return 0;
                        }
                    }
                }
            }
            i0 += 1;
        }

        r0 ^ ((r0 ^ -1) & -((r0 == n0 as i32) as i32))
    }
}
