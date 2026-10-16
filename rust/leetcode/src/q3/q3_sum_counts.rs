impl Solution {
    pub fn sum_counts(nums: Vec<i32>) -> i32 {
        const ZZ: i64 = 1_000_000_007;
        fn zz(aa: &mut [(i64, i64, i64)], bb: usize, cc: usize, dd: usize) {
            let (ee, ff, gg) = aa[bb];
            if gg == 0 {
                return;
            }
            let hh = (dd - cc + 1) as i64;
            aa[bb] = (
                (ee + gg * hh) % ZZ,
                (ff + 2 * gg * ee + gg * gg * hh) % ZZ,
                0,
            );
            if cc < dd {
                aa[bb * 2 + 1].2 += gg;
                aa[bb * 2 + 2].2 += gg;
            }
        }
        fn yy(aa: &mut [(i64, i64, i64)], bb: usize, cc: usize, dd: usize, ee: usize, ff: usize) {
            zz(aa, bb, cc, dd);
            if dd < ee || cc > ff {
                return;
            }
            if ee <= cc && dd <= ff {
                aa[bb].2 = 1;
                zz(aa, bb, cc, dd);
                return;
            }
            let gg = cc + (dd - cc) / 2;
            yy(aa, bb * 2 + 1, cc, gg, ee, ff);
            yy(aa, bb * 2 + 2, gg + 1, dd, ee, ff);
            aa[bb].0 = (aa[bb * 2 + 1].0 + aa[bb * 2 + 2].0) % ZZ;
            aa[bb].1 = (aa[bb * 2 + 1].1 + aa[bb * 2 + 2].1) % ZZ;
        }
        if nums.is_empty() {
            return 0;
        }
        let mut aa = vec![(0, 0, 0); 4 * nums.len()];
        let mut bb = std::collections::HashMap::new();
        let mut cc = 0;
        for (dd, &ee) in nums.iter().enumerate() {
            let ff = bb.insert(ee, dd).map_or(0, |gg| gg + 1);
            yy(&mut aa, 0, 0, nums.len() - 1, ff, dd);
            cc = (cc + aa[0].1) % ZZ;
        }
        cc as i32
    }
}
