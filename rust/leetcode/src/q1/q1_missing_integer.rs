impl Solution {
    pub fn missing_integer(nums: Vec<i32>) -> i32 {
        let mut a1 = nums[0];
        for a2 in 1..nums.len() {
            if nums[a2] == nums[a2 - 1] + 1 {
                a1 += nums[a2];
            } else {
                break;
            }
        }
        let mut a3 = [false; 51];
        for a4 in &nums {
            a3[*a4 as usize] = true;
        }
        while a1 < 51 && a3[a1 as usize] {
            a1 += 1;
        }
        a1
    }
}
