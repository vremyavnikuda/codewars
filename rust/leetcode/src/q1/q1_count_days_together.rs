impl Solution {
    pub fn count_days_together(
        arrive_alice: String,
        leave_alice: String,
        arrive_bob: String,
        leave_bob: String,
    ) -> i32 {
        const AA: [i32; 12] = [0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334];
        let bb =
            |cc: &str| AA[cc[..2].parse::<usize>().unwrap() - 1] + cc[3..].parse::<i32>().unwrap();
        (bb(&leave_alice).min(bb(&leave_bob)) - bb(&arrive_alice).max(bb(&arrive_bob)) + 1).max(0)
    }
}
