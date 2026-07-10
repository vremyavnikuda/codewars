impl Solution {
    pub fn find_disappeared_numbers(nums: Vec<i32>) -> Vec<i32> {
        let mut nums = nums;
        let q1 = nums.len();
        for q2 in 0..q1 {
            let q3 = nums[q2].abs() as usize - 1;
            if nums[q3] > 0 {
                nums[q3] = -nums[q3];
            }
        }
        (1..=q1).filter(|&q4| nums[q4 - 1] > 0).map(|q4| q4 as i32).collect()
    }
}
