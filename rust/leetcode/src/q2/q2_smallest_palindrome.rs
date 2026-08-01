impl Solution {
    pub fn smallest_palindrome(s: String) -> String {
        let mut q1 = [0u32; 26];
        for q2 in s.bytes() {
            q1[(q2 - b'a') as usize] += 1;
        }
        let mut q3 = Vec::new();
        let mut a1 = None;
        for a2 in 0..26u8 {
            let a3 = q1[a2 as usize] / 2;
            if a3 > 0 {
                q3.extend(std::iter::repeat(b'a' + a2).take(a3 as usize));
            }
            q1[a2 as usize] -= a3 * 2;
            if q1[a2 as usize] == 1 {
                a1 = Some(b'a' + a2);
            }
        }
        let mut a2 = String::with_capacity(s.len());
        a2.extend(q3.iter().map(|&q5| q5 as char));
        if let Some(q4) = a1 {
            a2.push(q4 as char);
        }
        a2.extend(q3.iter().rev().map(|&q5| q5 as char));
        a2
    }
}