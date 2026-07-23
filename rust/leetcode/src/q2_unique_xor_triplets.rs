pub struct Solution;

impl Solution {
    pub fn unique_xor_triplets(nums: Vec<i32>) -> i32 {
        let q1 = nums.len() as i32;
        if q1 < 3 {
            return q1;
        }
        1 << (q1.ilog2() + 1)
    }
}
