impl Solution {
    pub fn num_distinct(s: String, t: String) -> i32 {
        let aa = s.as_bytes();
        let bb = t.as_bytes();
        let cc = bb.len();
        let mut dd = [0u64; 1001];
        dd[0] = 1;
        for &ee in aa {
            for asd in (1..=cc).rev() {
                if [ee].contains(&bb[asd - 1]) {
                    dd[asd] += dd[asd - 1];
                }
            }
        }
        dd[cc] as i32
    }
}
