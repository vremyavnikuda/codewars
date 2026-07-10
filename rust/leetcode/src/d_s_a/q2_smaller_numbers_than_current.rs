impl Solution {
    pub fn smaller_numbers_than_current(nums: Vec<i32>) -> Vec<i32> {
        let mut q1 = [0i32; 101];
        for &q2 in &nums {
            q1[q2 as usize] += 1;
        }
        for q2 in 1..=100 {
            q1[q2] += q1[q2 - 1];
        }
        nums.iter().map(|&q2| if q2 == 0 { 0 } else { q1[(q2 - 1) as usize] }).collect()
    }
}