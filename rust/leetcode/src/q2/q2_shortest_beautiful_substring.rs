impl Solution {
    pub fn shortest_beautiful_substring(mut s: String, k: i32) -> String {
        if k <= 0 {
            s.clear();
            return s;
        }
        let q1 = s.as_bytes();
        let q2 = k as usize;
        let mut q3 = 0;
        let mut q4 = 0;
        let mut q5 = None;
        for q6 in 0..q1.len() {
            q4 += usize::from(q1[q6] == b'1');
            while q4 > q2 || (q4 == q2 && q1[q3] == b'0') {
                q4 -= usize::from(q1[q3] == b'1');
                q3 += 1;
            }
            if q4 == q2 {
                let q7 = &q1[q3..=q6];
                if q5.is_none_or(|q8: (usize, usize)| {
                    let q9 = &q1[q8.0..q8.1];
                    q7.len() < q9.len() || (q7.len() == q9.len() && q7 < q9)
                }) {
                    q5 = Some((q3, q6 + 1));
                }
            }
        }
        if let Some((q6, q7)) = q5 {
            s.truncate(q7);
            drop(s.drain(..q6));
        } else {
            s.clear();
        }
        s
    }
}
