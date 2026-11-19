impl Solution {
    pub fn minimize_sum(nums: Vec<i32>) -> i32 {
        let (aa, bb, cc, dd, ee, ff) = nums.iter().fold(
            (i32::MAX, i32::MAX, i32::MAX, i32::MIN, i32::MIN, i32::MIN),
            |(aa, bb, cc, dd, ee, ff), &xx| {
                let (aa, bb, cc) = if xx < aa {
                    (xx, aa, bb)
                } else if xx < bb {
                    (aa, xx, bb)
                } else if xx < cc {
                    (aa, bb, xx)
                } else {
                    (aa, bb, cc)
                };
                let (dd, ee, ff) = if xx > ff {
                    (ee, ff, xx)
                } else if xx > ee {
                    (ee, xx, ff)
                } else if xx > dd {
                    (xx, ee, ff)
                } else {
                    (dd, ee, ff)
                };
                (aa, bb, cc, dd, ee, ff)
            },
        );
        (dd - aa).min(ee - bb).min(ff - cc)
    }
}
