impl Solution {
    pub fn count_consistent(nums: Vec<i32>) -> i32 {
        let mut aa = 0i32;
        for bb in 0..nums.len() {
            let mut cc = nums[bb];
            let mut dd = nums[bb];
            for ee in bb..nums.len() {
                cc &= nums[ee];
                if nums[ee] < dd {
                    dd = nums[ee];
                }
                if cc == dd {
                    aa += 1;
                }
            }
        }
        aa
    }
}
