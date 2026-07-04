impl Solution {
    pub fn interleave_characters(word1: String, word2: String, target: String) -> i32 {
        let q1: i64 = 1_000_000_007;
        let q2 = word1.as_bytes();
        let q3 = word2.as_bytes();
        let q4 = target.as_bytes();
        let q5 = q2.len();
        let q6 = q3.len();
        let mut a1 = vec![vec![1i64; q6 + 1]; q5 + 1];
        for &a2 in q4 {
            let mut a3 = vec![vec![0i64; q6 + 1]; q5 + 1];
            let mut a4 = vec![vec![0i64; q6 + 1]; q5 + 1];
            for a5 in 1..=q5 {
                for a6 in 0..=q6 {
                    let a7 = if q2[a5 - 1] == a2 { a1[a5 - 1][a6] } else { 0 };
                    a3[a5][a6] = (a3[a5 - 1][a6] + a7) % q1;
                }
            }
            for a6 in 1..=q6 {
                for a5 in 0..=q5 {
                    let a8 = if q3[a6 - 1] == a2 { a1[a5][a6 - 1] } else { 0 };
                    a4[a5][a6] = (a4[a5][a6 - 1] + a8) % q1;
                }
            }
            let mut a9 = vec![vec![0i64; q6 + 1]; q5 + 1];
            for a5 in 0..=q5 {
                for a6 in 0..=q6 {
                    a9[a5][a6] = (a3[a5][a6] + a4[a5][a6]) % q1;
                }
            }
            a1 = a9;
        }
        let a10 = (a1[q5][q6] - a1[q5][0] - a1[0][q6] + 2 * q1) % q1;
        a10 as i32
    }
}
