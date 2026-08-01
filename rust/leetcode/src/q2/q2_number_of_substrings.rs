impl Solution {
    pub fn number_of_substrings(s: String) -> i32 {
        let mut q1 = [-1i32; 3];
        s.as_bytes().iter().enumerate().fold(0i32, |a1, (q2, &q3)| {
            q1[(q3 - b'a') as usize] = q2 as i32;
            a1 + q1[0].min(q1[1]).min(q1[2]) + 1
        })
    }
}
