impl Solution {
    pub fn sequential_digits(low: i32, high: i32) -> Vec<i32> {
        (2..10)
            .flat_map(|q1| {
                (1..=10 - q1).map(move |q2| {
                    (0..q1).fold(0, |q3, q4| q3 * 10 + q2 + q4)
                })
            })
            .filter(|&q5| q5 >= low && q5 <= high)
            .collect()
    }
}
