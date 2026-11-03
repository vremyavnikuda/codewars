impl Solution {
    pub fn min_moves(nums: Vec<i32>) -> i32 {
        let aa = nums.len() as i32;
        let (bb, cc) = nums
            .iter()
            .fold((0, 0), |(bb, cc), &dd| (bb.max(dd), cc + dd));
        bb * aa - cc
    }
}
