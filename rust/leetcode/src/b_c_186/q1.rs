impl Solution {
    pub fn is_middle_element_unique(nums: Vec<i32>) -> bool {
        let q1 = nums.len() / 2;
        let q2 = nums[q1];
        nums.iter().filter(|&&a1| a1 == q2).count() == 1
    }
}
