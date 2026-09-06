impl Solution {
    pub fn count_rotations(s: String, k: i32) -> i32 {
        let aa = s.as_bytes();
        let bb = aa.windows(2).filter(|cc| cc[0] == cc[1]).count() as i32
            + (aa[0] == aa[aa.len() - 1]) as i32;
        if k == bb {
            aa.len() as i32 - bb
        } else if k == bb - 1 {
            bb
        } else {
            0
        }
    }
}
