impl Solution {
    pub fn min_changes(s: String) -> i32 {
        s.as_bytes().chunks(2).filter(|aa| aa[0] != aa[1]).count() as i32
    }
}
