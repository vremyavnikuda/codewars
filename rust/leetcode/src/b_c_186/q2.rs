impl Solution {
    pub fn max_valid_pair_sum(nums: Vec<i32>, k: i32) -> i32 {
        let q1 = k as usize;
        nums.iter()
            .enumerate()
            .skip(q1)
            .fold((i32::MIN, i32::MIN), |(q2, q3), (a1, &a2)| {
                let a3 = q2.max(nums[a1 - q1]);
                (a3, q3.max(a3 + a2))
            })
            .1
    }
}
