impl Solution {
    pub fn count_subarrays(nums: Vec<i32>, min_k: i32, max_k: i32) -> i64 {
        let mut run = 0i64;
        nums.iter()
            .map(|&x| {
                run = if (min_k..=max_k).contains(&x) {
                    run + 1
                } else {
                    0
                };
                run
            })
            .sum()
    }
}
