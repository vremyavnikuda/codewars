impl Solution {
    pub fn count_valid_selections(nums: Vec<i32>) -> i32 {
        let total_sum: i32 = nums.iter().sum();
        let mut valid_count = 0;
        let mut left_sum = 0;
        for &current_num in &nums {
            if current_num != 0 {
                left_sum += current_num;
            } else {
                let right_sum = total_sum - left_sum;
                if left_sum == right_sum {
                    valid_count += 2;
                } else if (left_sum - right_sum).abs() == 1 {
                    valid_count += 1;
                }
            }
        }
        valid_count
    }
}
