impl Solution {
    pub fn sort_permutation(nums: Vec<i32>) -> i32 {
        nums.iter()
            .enumerate()
            .filter(|&(aa, &bb)| aa != bb as usize)
            .fold(-1, |aa, (_, &bb)| aa & bb)
            .max(0)
    }
}
