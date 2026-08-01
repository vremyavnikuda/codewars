impl Solution {
    pub fn max_walls(robots: Vec<i32>, distance: Vec<i32>, walls: Vec<i32>) -> i32 {
        #[inline(always)]
        fn b(v: &[i32], x: i32, p: bool) -> usize {
            let (mut l, mut r) = (0usize, v.len());
            while l < r {
                let m = (l + r) >> 1;
                let y = v[m];
                if if p { y <= x } else { y < x } {
                    l = m + 1;
                } else {
                    r = m;
                }
            }
            l
        }
        let n = robots.len();
        if n == 0 {
            return 0;
        }
        let mut a: Vec<(i32, i32)> = robots.into_iter().zip(distance).collect();
        a.sort_unstable_by_key(|z| z.0);
        let mut w = walls;
        w.sort_unstable();
        let s = w.as_slice();
        let (mut d0, mut d1) = (0i32, 0i32);
        let mut i = 0usize;
        while i < n {
            let (x, d) = a[i];
            let mut l = x - d;
            if i != 0 {
                let t = a[i - 1].0 + 1;
                if l < t {
                    l = t;
                }
            }
            let xl = b(s, x, false);
            let xu = b(s, x, true);
            let base = d0 + (xu - b(s, l, false)) as i32;
            let mut r0 = x + d;
            let mut r1 = r0;
            if i + 1 < n {
                let (nx, nd) = a[i + 1];
                let t0 = nx - nd - 1;
                let t1 = nx - 1;
                if r0 > t0 {
                    r0 = t0;
                }
                if r1 > t1 {
                    r1 = t1;
                }
            }
            let c0 = d1 + (b(s, r0, true) - xl) as i32;
            let c1 = d1 + (b(s, r1, true) - xl) as i32;
            d0 = if base > c0 { base } else { c0 };
            d1 = if base > c1 { base } else { c1 };
            i += 1;
        }
        d1
    }
}
