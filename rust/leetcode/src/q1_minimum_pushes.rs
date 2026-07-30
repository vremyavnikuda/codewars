impl Solution {
    pub fn minimum_pushes(word: String) -> i32 {
        let q1 = word.len() as i32;
        let (q2, q3) = (q1 / 8, q1 % 8);
        (1..=q2).fold(0, |q4, q5| q4 + q5 * 8) + (q2 + 1) * q3
    }
}