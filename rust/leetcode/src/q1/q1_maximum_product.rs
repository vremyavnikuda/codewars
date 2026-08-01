impl Solution {
    pub fn maximum_product(nums: Vec<i32>) -> i32 {
        let mut q1 = nums;
        q1.sort();
        let q2 = q1.len();
        let a1 = q1[q2 - 1] * q1[q2 - 2] * q1[q2 - 3];
        let a2 = q1[q2 - 1] * q1[0] * q1[1];
        a1.max(a2)
    }
}
