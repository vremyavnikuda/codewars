impl Solution {
    pub fn count_magical_pairs(s: String) -> i32 {
        let s = s.as_bytes();
        let n = s.len();
        let mut ans = 0i64;
        for j in 0..n - 1 {
            let mut left = [0i64; 27];
            let mut mask = 0u32;
            for i in (0..=j).rev() {
                mask |= 1 << (s[i] - b'a');
                left[mask.count_ones() as usize] += 1;
            }
            let mut mask = 0u32;
            for k in j + 1..n {
                mask |= 1 << (s[k] - b'a');
                ans += left[mask.count_ones() as usize];
            }
        }
        ans as i32
    }
}
