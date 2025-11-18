impl Solution {
    pub fn k_length_apart(nums: Vec<i32>, k: i32) -> bool {
        let mut prev_one: i32 = -(k + 1);
        for (idx, value) in nums.into_iter().enumerate() {
            if value == 1 {
                if idx as i32 - prev_one - 1 < k {
                    return false;
                }
                prev_one = idx as i32;
            }
        }
        true
    }
}
