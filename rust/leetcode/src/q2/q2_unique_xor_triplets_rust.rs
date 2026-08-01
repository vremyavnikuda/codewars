impl Solution {
    pub fn unique_xor_triplets(nums: Vec<i32>) -> i32 {
        let q1 = (nums.iter().max().copied().unwrap_or(0) << 1) as usize;
        let mut q2 = vec![false; q1];
        for &q3 in &nums {
            for &q4 in &nums {
                q2[(q3 ^ q4) as usize] = true;
            }
        }
        let mut q5 = vec![0; q1];
        for (q6, &q7) in q2.iter().enumerate() {
            if q7 {
                for &q8 in &nums {
                    q5[(q6 ^ (q8 as usize)) as usize] = 1;
                }
            }
        }
        q5.iter().sum()
    }
}
