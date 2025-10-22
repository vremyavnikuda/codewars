impl Solution {
    pub fn has_increasing_subarrays(nums: Vec<i32>, k: i32) -> bool {
        if k == 0 {
            return true;
        }
        let mut max_valid_length = 0;
        let mut previous_length = 0;
        let mut current_length = 0;
        let n = nums.len();
        for i in 0..n {
            current_length += 1;
            if i == n - 1 || nums[i] >= nums[i + 1] {
                max_valid_length = std::cmp::max(
                    max_valid_length, 
                    std::cmp::max(current_length / 2, std::cmp::min(previous_length, current_length))
                );
                previous_length = current_length;
                current_length = 0;
            }
        }
        max_valid_length >= k as usize
    }
}
