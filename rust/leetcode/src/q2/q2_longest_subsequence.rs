impl Solution {
    pub fn longest_subsequence(nums: Vec<i32>) -> i32 {
        let q1: i32 = nums.iter().fold(0, |q2, &q3| q2 ^ q3);
        let q4 = nums.iter().filter(|&&q5| q5 == 0).count();
        if q1 != 0 {
            return nums.len() as i32;
        }
        if q4 == nums.len() {
            0
        } else {
            nums.len() as i32 - 1
        }
    }
}