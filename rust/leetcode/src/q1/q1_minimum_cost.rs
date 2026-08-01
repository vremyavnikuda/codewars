struct Solution;

impl Solution {
    pub fn minimum_cost(nums: Vec<i32>) -> i32 {
        let a0 = nums[0];
        let mut b1 = 100;
        let mut c2 = 100;
        for &v in nums.iter().skip(1) {
            if v < b1 {
                c2 = b1;
                b1 = v;
            } else if v < c2 {
                c2 = v;
            }
        }
        a0 + b1 + c2
    }
}
