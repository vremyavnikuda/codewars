impl Solution {
    pub fn check_divisibility(n: i32) -> bool {
        let (q1, q2) = std::iter::successors(Some(n), |&a1| (a1 >= 10).then(|| a1 / 10))
            .map(|a1| a1 % 10)
            .fold((0i32, 1i32), |(a1, a2), a3| (a1 + a3, a2 * a3));
        n % (q1 + q2) == 0
    }
}
