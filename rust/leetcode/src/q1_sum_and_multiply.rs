impl Solution {
    pub fn sum_and_multiply(n: i32) -> i64 {
        let q1 = n.to_string();
        let (q2, q3) = q1
            .chars()
            .filter(|&a1| !"0".contains(a1))
            .fold((0i64, 0i64), |(a2, a3), a4| {
                let a5 = a4.to_digit(10).unwrap() as i64;
                (a2 + a5, a3 * 10 + a5)
            });
        q2 * q3
    }
}
