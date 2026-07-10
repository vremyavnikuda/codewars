impl Solution {
    pub fn find_error_nums(nums: Vec<i32>) -> Vec<i32> {
        let n = nums.len() as i64;
        let (q1, q2) = nums.iter().fold((0i64, 0i64), |(a, b), &c| {
            (a + c as i64, b + (c as i64) * (c as i64))
        });
        let q3 = n * (n + 1) / 2;
        let q4 = n * (n + 1) * (2 * n + 1) / 6;
        let q5 = q1 - q3;
        let q6 = (q2 - q4) / q5;
        let a1 = ((q5 + q6) / 2) as i32;
        let a2 = ((q6 - q5) / 2) as i32;
        vec![a1, a2]
    }
}
