impl Solution {
    pub fn can_make_subsequence(s: String, t: String) -> bool {
        let q1 = s.as_bytes();
        let q2 = t.as_bytes();
        let q3 = q1.len();
        let q4 = q2.len();
        let mut q5 = vec![0usize; q3 + 1];
        q5[q3] = q4;
        let mut a1 = q4;
        let mut a2 = q3;
        while a1 > 0 {
            a1 -= 1;
            if a2 > 0 && q1[a2 - 1] == q2[a1] {
                a2 -= 1;
                q5[a2] = a1;
            }
        }
        if q5[1] > 0 {
            return true;
        }
        let mut a3 = 0usize;
        for a4 in 0..q4 {
            if a3 < q3 && q1[a3] == q2[a4] {
                a3 += 1;
                if a3 == q3 {
                    return true;
                }
                if q5[a3 + 1] > a4 + 1 {
                    return true;
                }
            }
        }
        false
    }
}
