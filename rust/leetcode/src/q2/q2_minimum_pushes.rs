impl Solution {
    pub fn minimum_pushes(word: String) -> i32 {
        let mut q1 = [0usize; 26];
        for q2 in word.bytes() {
            q1[(q2 - b'a') as usize] += 1;
        }
        q1.sort_unstable_by(|q3, q4| q4.cmp(q3));
        q1.iter()
            .enumerate()
            .fold(0, |q5, (q6, &q7)| q5 + ((q6 / 8 + 1) * q7) as i32)
    }
}
