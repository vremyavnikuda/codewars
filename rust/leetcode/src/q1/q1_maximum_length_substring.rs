impl Solution {
    pub fn maximum_length_substring(s: String) -> i32 {
        let a1 = s.as_bytes();
        let mut a2 = [0i32; 26];
        let mut a3 = 0;
        let mut a4 = 0;
        for (a5, &a6) in a1.iter().enumerate() {
            let a7 = (a6 - b'a') as usize;
            a2[a7] += 1;
            while a2[a7] > 2 {
                a2[(a1[a3] - b'a') as usize] -= 1;
                a3 += 1;
            }
            a4 = a4.max(a5 - a3 + 1);
        }
        a4 as i32
    }
}
