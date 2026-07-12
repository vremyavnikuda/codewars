impl Solution {
    pub fn seconds_between_times(start_time: String, end_time: String) -> i32 {
        let q1 = |q2: &str| -> i32 {
            q2.split(':').fold(0, |a1, a2| a1 * 60 + a2.parse::<i32>().unwrap())
        };
        let q3 = q1(&end_time) - q1(&start_time);
        if q3 < 0 { q3 + 86400 } else { q3 }
    }
}