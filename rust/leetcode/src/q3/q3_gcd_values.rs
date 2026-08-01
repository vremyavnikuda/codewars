impl Solution {
    pub fn gcd_values(nums: Vec<i32>, queries: Vec<i64>) -> Vec<i32> {
        let q1 = nums.iter().copied().max().unwrap_or(0) as usize;
        let mut q2 = vec![0_i64; q1 + 1];
        let mut q3 = vec![0_i64; q1 + 1];
        for q4 in nums {
            q2[q4 as usize] += 1;
        }
        for q4 in (1..=q1).rev() {
            let mut q5 = 0_i64;
            let mut q6 = q4;
            while q6 <= q1 {
                q5 += q2[q6];
                let q7 = q3[q6];
                q3[q4] -= q7;
                q6 += q4;
            }
            q3[q4] += q5 * (q5 - 1) / 2;
        }
        for q4 in 2..=q1 {
            q3[q4] += q3[q4 - 1];
        }
        queries
            .into_iter()
            .map(|q4| q3.partition_point(|q5| *q5 <= q4) as i32)
            .collect()
    }
}
