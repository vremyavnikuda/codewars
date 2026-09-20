impl Solution {
    pub fn reverse_degree(s: String) -> i32 {
        s.bytes().enumerate().fold(0, |aa, (bb, cc)| {
            aa + ((bb + 1) as i32) * (26 - (cc - b'a') as i32)
        })
    }
}
