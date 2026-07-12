impl Solution {
    pub fn minimum_cost(nums: Vec<i32>, k: i32) -> i32 {
        let a1: i64 = 1_000_000_007;
        let a6 = k as i64;
        let (_, _, q1) = nums.iter().fold((a6, 0i64, 0i64), |(q2, q3, q4), &a2| {
            let a2 = a2 as i64;
            let (q2, q3, q4) = if q2 < a2 {
                let a3 = a2 - q2;
                let a4 = (a3 + a6 - 1) / a6;
                let a5 = (a4 as i128) * (2 * (q3 as i128) + a4 as i128 + 1) / 2;
                (
                    q2 + a4 * a6,
                    q3 + a4,
                    ((q4 as i128 + a5) % a1 as i128) as i64,
                )
            } else {
                (q2, q3, q4)
            };
            (q2 - a2, q3, q4)
        });
        q1 as i32
    }
}
