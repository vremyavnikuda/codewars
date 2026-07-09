impl Solution {
    pub fn path_existence_queries(n: i32, nums: Vec<i32>, max_diff: i32, queries: Vec<Vec<i32>>) -> Vec<bool> {
        let q1 = n as usize;
        let mut q2 = vec![0i32; q1];
        let mut q3 = 0i32;
        for q4 in 1..q1 {
            if nums[q4] - nums[q4 - 1] > max_diff {
                q3 += 1;
            }
            q2[q4] = q3;
        }
        queries.iter().map(|q5| q2[q5[0] as usize] == q2[q5[1] as usize]).collect()
    }
}