impl Solution {
    pub fn min_swaps(grid: Vec<Vec<i32>>) -> i32 {
        let n = grid.len();
        let mut z = vec![-1_i32; n];
        let mut a = 0usize;
        while a < n {
            let r = unsafe { grid.get_unchecked(a) };
            let mut b = n;
            while b != 0 {
                b -= 1;
                if unsafe { *r.get_unchecked(b) } != 0 {
                    unsafe { *z.get_unchecked_mut(a) = b as i32 };
                    break;
                }
            }
            a += 1;
        }
        let mut s = 0_i32;
        let mut i = 0usize;
        while i < n {
            let t = i as i32;
            let mut j = i;
            while j < n && unsafe { *z.get_unchecked(j) } > t {
                j += 1;
            }
            if j == n {
                return -1;
            }
            s += (j - i) as i32;
            while j > i {
                z.swap(j, j - 1);
                j -= 1;
            }
            i += 1;
        }
        s
    }
}
