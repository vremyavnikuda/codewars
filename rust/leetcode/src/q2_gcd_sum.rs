impl Solution {
    pub fn gcd_sum(nums: Vec<i32>) -> i64 {
        fn q1(mut q2: i32, mut q3: i32) -> i32 {
            while q3 != 0 {
                let q4 = q2 % q3;
                q2 = q3;
                q3 = q4;
            }

            q2.abs()
        }
        let mut q2 = nums;
        let mut q3 = 0;
        q2.iter_mut().for_each(|q4| {
            q3 = q3.max(*q4);
            *q4 = q1(*q4, q3);
        });
        q2.sort_unstable();
        let q4 = q2.len();
        (0..q4 / 2).fold(0_i64, |q5, q6| q5 + q1(q2[q6], q2[q4 - q6 - 1]) as i64)
    }
}
