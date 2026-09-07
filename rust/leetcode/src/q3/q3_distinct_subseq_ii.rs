impl Solution {
    pub fn distinct_subseq_ii(s: String) -> i32 {
        let aa = 1_000_000_007i64;
        let mut bb = [0i64; 26];
        for &cc in s.as_bytes() {
            let dd = (cc - b'a') as usize;
            bb[dd] = (bb.iter().sum::<i64>() + 1) % aa;
        }
        (bb.iter().sum::<i64>() % aa) as i32
    }
}
