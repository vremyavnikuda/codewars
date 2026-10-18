impl Solution {
    pub fn min_deletions(nums: Vec<i32>) -> i32 {
        nums.windows(2).filter(|w| w[0] == w[1]).count() as i32
    }
}
