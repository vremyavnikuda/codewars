impl Solution {
    pub fn min_operations(s1: String, s2: String) -> i32 {
        let q1 = s1.as_bytes();
        let q2 = s2.as_bytes();
        if q1.len() == 1 {
            return match (q1[0], q2[0]) {
                (a1, a2) if a1 == a2 => 0,
                (b'0', b'1') => 1,
                _ => -1,
            };
        }
        let (q3, q4) = q1
            .iter()
            .zip(q2.iter())
            .fold((0i32, 0i32), |(a1, a2), (&a3, &a4)| {
                if a3 == b'1' && a4 == b'0' {
                    (a1, a2 + 1)
                } else {
                    let a5 = a1 + a2 / 2 + 2 * (a2 % 2) + if a3 == b'0' && a4 == b'1' { 1 } else { 0 };
                    (a5, 0)
                }
            });
        q3 + q4 / 2 + 2 * (q4 % 2)
    }
}
