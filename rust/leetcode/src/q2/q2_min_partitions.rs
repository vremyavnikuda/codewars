impl Solution {
    pub fn min_partitions(n: String) -> i32 {
        let z = n.as_bytes();
        let mut i = 0usize;
        let mut m = b'0';
        while i < z.len() {
            let x = unsafe { *z.get_unchecked(i) };
            m ^= (m ^ x) & (((m < x) as u8).wrapping_neg());
            if m == b'9' {
                break;
            }
            i += 1;
        }
        i32::from(m & 15)
    }
}
