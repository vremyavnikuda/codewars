impl Solution {
    pub fn smallest_subsequence(s: String) -> String {
        let mut q1 = s.into_bytes();
        let mut q2 = [0usize; 26];
        for (q3, q4) in q1.iter().enumerate() {
            q2[(q4 - b'a') as usize] = q3;
        }
        let mut q3 = 0usize;
        for q4 in 0..q1.len() {
            let q5 = q1[q4];
            if q1[..q3].contains(&q5) {
                continue;
            }
            while q3 > 0 && q1[q3 - 1] > q5 && q2[(q1[q3 - 1] - b'a') as usize] > q4 {
                q3 -= 1;
            }
            q1[q3] = q5;
            q3 += 1;
        }
        q1.truncate(q3);
        String::from_utf8(q1).unwrap()
    }
}
