impl Solution {
    pub fn sum_decoded(nums: Vec<i64>) -> i32 {
        nums.iter().fold(0_i64, |aa, &bb| {
            let cc = bb % 10;
            let dd = bb / 10;
            let ee = 10_i64.pow(dd.ilog10() + 1 - cc as u32);
            let ff = dd / ee;
            let gg = dd % ee;
            let hh = std::iter::successors(Some((ff, gg)), |&(aa, bb)| {
                (bb > 1).then(|| (aa * aa % 1_000_000_007, bb / 2))
            })
            .fold(1_i64, |aa, (bb, cc)| {
                if cc % 2 == 1 {
                    aa * bb % 1_000_000_007
                } else {
                    aa
                }
            });

            (aa + hh) % 1_000_000_007
        }) as i32
    }
}
