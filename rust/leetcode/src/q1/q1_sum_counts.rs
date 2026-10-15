impl Solution {
    pub fn sum_counts(nums: Vec<i32>) -> i32 {
        let mut aa = 0;
        for bb in 0..nums.len() {
            let mut cc = [false; 101];
            let mut dd = 0;
            for &ee in &nums[bb..] {
                if !cc[ee as usize] {
                    cc[ee as usize] = true;
                    dd += 1;
                }
                aa += dd * dd;
            }
        }
        aa
    }
}
