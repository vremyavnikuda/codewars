pub struct Solution;

impl Solution {
    pub fn sum_and_multiply(s: String, queries: Vec<Vec<i32>>) -> Vec<i32> {
        const MOD: i64 = 1_000_000_007;
        const MX: usize = 100_001;
        static Q1: std::sync::OnceLock<Vec<i64>> = std::sync::OnceLock::new();
        let q1 = Q1.get_or_init(|| {
            let mut q2 = vec![0i64; MX];
            q2[0] = 1;
            for q3 in 1..MX {
                q2[q3] = q2[q3 - 1] * 10 % MOD;
            }
            q2
        });
        let q2 = s.len();
        let mut q3 = vec![0i64; q2 + 1];
        let mut q4 = vec![0i32; q2 + 1];
        let mut q5 = vec![0i32; q2 + 1];
        for (a1, a2) in s.chars().enumerate() {
            let a3 = a2.to_digit(10).unwrap() as i32;
            let a4 = a1 + 1;
            q4[a4] = q4[a1] + a3;
            let a5 = if "0".contains(a2) { 0 } else { 1 };
            q5[a4] = q5[a1] + a5;
            q3[a4] = if a5 == 1 {
                (q3[a1] * 10 + a3 as i64) % MOD
            } else {
                q3[a1]
            };
        }
        let mut q6 = Vec::with_capacity(queries.len());
        for a6 in &queries {
            let a7 = a6[0] as usize;
            let a8 = a6[1] as usize;
            let a9 = q5[a8 + 1] - q5[a7];
            let a10 = q4[a8 + 1] - q4[a7];
            let a11 = (q3[a8 + 1] - q3[a7] * q1[a9 as usize] % MOD + MOD) % MOD;
            q6.push((a11 * a10 as i64 % MOD) as i32);
        }
        q6
    }
}
