impl Solution {
    pub fn create_grid(m: i32, n: i32) -> Vec<String> {
        if m <= 0 {
            return Vec::new();
        }
        let aa = n.max(0) as usize;
        let bb = ".".repeat(aa);
        let mut cc = String::with_capacity(aa);
        cc.extend(std::iter::repeat('#').take(aa.saturating_sub(1)));
        if aa > 0 {
            cc.push('.');
        }
        std::iter::once(bb)
            .chain(std::iter::repeat(cc).take((m - 1) as usize))
            .collect()
    }
}
