impl Solution {
    pub fn max_product(nums: Vec<i32>) -> i32 {
        let (a1, a2) = nums.into_iter().fold((0, 0), |(q1, q2), a3| {
            if a3 > q1 {
                (a3, q1)
            } else if a3 > q2 {
                (q1, a3)
            } else {
                (q1, q2)
            }
        });
        (a1 - 1) * (a2 - 1)
    }
}