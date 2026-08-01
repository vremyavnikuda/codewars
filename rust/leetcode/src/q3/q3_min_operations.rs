pub struct Solution;

impl Solution {
    #[inline(always)]
    fn f(p: &mut [usize], mut x: usize) -> usize {
        while p[x] != x {
            let y = p[x];
            p[x] = p[y];
            x = y;
        }
        x
    }

    pub fn min_operations(s: String, k: i32) -> i32 {
        let n = s.len() as i32;
        let mut z = 0i32;
        for &c in s.as_bytes() {
            z += (c == b'0') as i32;
        }

        let mut p: Vec<usize> = (0..(n as usize + 3)).collect();
        let zi = z as usize;
        p[zi] = Self::f(&mut p, zi + 2);

        let mut q: Vec<i32> = Vec::with_capacity((n + 1) as usize);
        q.push(z);

        let mut h = 0usize;
        let mut d = 0i32;
        while h < q.len() {
            let e = q.len();
            while h < e {
                let c = q[h];
                h += 1;
                if c == 0 {
                    return d;
                }

                let a = if c < k { c } else { k };
                let b0 = k - n + c;
                let b = if b0 > 0 { b0 } else { 0 };
                let l = (c + k - (a << 1)) as usize;
                let r = (c + k - (b << 1)) as usize;

                let mut x = Self::f(&mut p, l);
                while x <= r {
                    q.push(x as i32);
                    p[x] = Self::f(&mut p, x + 2);
                    x = Self::f(&mut p, x);
                }
            }
            d += 1;
        }
        -1
    }
}
