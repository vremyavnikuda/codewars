impl Solution {
    pub fn find_gcd(nums: Vec<i32>) -> i32 {
        let (mut q1, mut q2) = nums
            .iter()
            .copied()
            .fold((nums[0], nums[0]), |(q1, q2), q3| (q1.min(q3), q2.max(q3)));

        while q2 != 0 {
            let q3 = q1 % q2;
            q1 = q2;
            q2 = q3;
        }

        q1
    }
}
