impl Solution {
    #[inline(always)]
    pub fn minimum_total_distance(robot: Vec<i32>, factory: Vec<Vec<i32>>) -> i64 {
        let mut robot = robot;
        let mut factory = factory;
        robot.sort_unstable();
        factory.sort_unstable_by(|a, b| a[0].cmp(&b[0]));

        let n = robot.len();
        if n == 0 {
            return 0;
        }
        const I: i64 = 3_000_000_000_000_000_000;
        let mut d = vec![I; n + 1];
        d[n] = 0;
        let p = robot.as_ptr();

        let mut j = factory.len();
        while j != 0 {
            j -= 1;
            let (x, c) = unsafe {
                (
                    *factory.get_unchecked(j).get_unchecked(0) as i64,
                    *factory.get_unchecked(j).get_unchecked(1) as usize,
                )
            };
            let mut i = 0usize;
            while i < n {
                let mut r = unsafe { *d.get_unchecked(i) };
                let mut s = 0i64;
                let mut k = 0usize;
                let z = (n - i).min(c);
                while k < z {
                    let q = unsafe { *p.add(i + k) as i64 } - x;
                    s += q.abs();
                    let v = s + unsafe { *d.get_unchecked(i + k + 1) };
                    if v < r {
                        r = v;
                    }
                    k += 1;
                }
                unsafe {
                    *d.get_unchecked_mut(i) = r;
                }
                i += 1;
            }
        }
        d[0]
    }
}
