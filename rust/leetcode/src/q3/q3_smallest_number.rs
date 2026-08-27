pub struct Solution;

impl Solution {
    const D: [[i32; 4]; 10] = [
        [0, 0, 0, 0],
        [0, 0, 0, 0],
        [1, 0, 0, 0],
        [0, 1, 0, 0],
        [2, 0, 0, 0],
        [0, 0, 1, 0],
        [1, 1, 0, 0],
        [0, 0, 0, 1],
        [3, 0, 0, 0],
        [0, 2, 0, 0],
    ];
    pub fn smallest_number(num: String, t: i64) -> String {
        let (q1, q2) = Self::z1(t);
        if !q2 {
            return "-1".to_string();
        }
        let a1 = Self::z3(&q1);
        if Self::z5(&a1) > num.len() as i32 {
            let mut s = String::with_capacity(num.len());
            Self::z4(&a1, &mut s);
            return s;
        }
        let mut q3 = Self::z2(&num);
        let mut a2 = num.find('0');
        if a2.is_none() {
            a2 = Some(num.len());
            if q1.iter().zip(q3.iter()).all(|(x, y)| x <= y) {
                return num;
            }
        }
        let q4 = num.len();
        for i in (0..q4).rev() {
            let q5 = num.as_bytes()[i] - b'0';
            q3 = Self::z6(q3, Self::D[q5 as usize]);
            let a3 = q4 - 1 - i;
            if i > a2.unwrap() {
                continue;
            }
            for q6 in q5 as i32 + 1..10 {
                let a4 = Self::z3(&Self::z6(Self::z6(q1, q3), Self::D[q6 as usize]));
                if Self::z5(&a4) <= a3 as i32 {
                    let a5 = a3 as i32 - Self::z5(&a4);
                    let mut s = String::with_capacity(q4 + 1);
                    s.push_str(&num[..i]);
                    s.push((b'0' + q6 as u8) as char);
                    s.extend(std::iter::repeat('1').take(a5 as usize));
                    Self::z4(&a4, &mut s);
                    return s;
                }
            }
        }
        let a6 = Self::z3(&q1);
        let mut s = String::with_capacity(q4 + 1);
        s.extend(std::iter::repeat('1').take(q4 + 1 - Self::z5(&a6) as usize));
        Self::z4(&a6, &mut s);
        s
    }
    fn z1(mut t: i64) -> ([i32; 4], bool) {
        let mut q = [0; 4];
        for (i, p) in [2i64, 3, 5, 7].iter().enumerate() {
            while t % p == 0 {
                t /= p;
                q[i] += 1;
            }
        }
        (q, t == 1)
    }
    fn z2(n: &str) -> [i32; 4] {
        let mut q = [0; 4];
        for c in n.bytes() {
            for i in 0..4 {
                q[i] += Self::D[(c - b'0') as usize][i];
            }
        }
        q
    }
    fn z3(c: &[i32; 4]) -> [i32; 10] {
        let q1 = c[0] / 3;
        let q2 = c[0] % 3;
        let q3 = c[1] / 2;
        let mut q4 = c[1] % 2;
        let mut q5 = q2 / 2;
        let mut q6 = q2 % 2;
        let mut q7 = 0;
        if q6 == 1 && q4 == 1 {
            q6 = 0;
            q4 = 0;
            q7 = 1;
        }
        if q4 == 1 && q5 == 1 {
            q6 = 1;
            q7 = 1;
            q4 = 0;
            q5 = 0;
        }
        [0, 0, q6, q4, q5, c[2], q7, c[3], q1, q3]
    }
    fn z4(f: &[i32; 10], s: &mut String) {
        for d in 2..10 {
            for _ in 0..f[d] {
                s.push((b'0' + d as u8) as char);
            }
        }
    }
    fn z5(f: &[i32; 10]) -> i32 {
        f.iter().sum()
    }
    fn z6(mut a: [i32; 4], b: [i32; 4]) -> [i32; 4] {
        for i in 0..4 {
            a[i] = (a[i] - b[i]).max(0);
        }
        a
    }
}
