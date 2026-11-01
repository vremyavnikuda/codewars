impl Solution {
    pub fn min_merged_integer(nums: Vec<i32>) -> i32 {
        nums.chunks(2)
            .map(|p| p[0] * 10i32.pow(p[1].ilog10() + 1) + p[1])
            .min()
            .unwrap()
    }
}
