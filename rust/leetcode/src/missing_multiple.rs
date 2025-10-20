use std::collections::HashSet;
struct Solution;

impl Solution {
    pub fn missing_multiple(nums: Vec<i32>, k: i32) -> i32 {
        let num_set: HashSet<i32> = nums.into_iter().collect();

        let mut mult = k;
        while num_set.contains(&mult) {
            mult += k;
        }
        mult
    }
}
