pub struct Solution;

impl Solution {
    pub fn make_largest_special(s: String) -> String {
        #[inline]
        fn q(x: &[u8]) -> Vec<u8> {
            if x.is_empty() {
                return Vec::new();
            }
            let mut a: Vec<Vec<u8>> = Vec::new();
            let (mut i, mut j, mut k) = (0usize, 0usize, 0i32);
            while i < x.len() {
                k += ((x[i] == b'1') as i32) * 2 - 1;
                if k == 0 {
                    let mut t = q(&x[j + 1..i]);
                    let mut u = Vec::with_capacity(t.len() + 2);
                    u.push(b'1');
                    u.append(&mut t);
                    u.push(b'0');
                    a.push(u);
                    j = i + 1;
                }
                i += 1;
            }
            a.sort_unstable_by(|l, r| r.cmp(l));
            let mut z = Vec::with_capacity(x.len());
            for w in a {
                z.extend_from_slice(&w);
            }
            z
        }

        if s.is_empty() {
            return s;
        }
        let y = q(s.as_bytes());
        unsafe { String::from_utf8_unchecked(y) }
    }
}
