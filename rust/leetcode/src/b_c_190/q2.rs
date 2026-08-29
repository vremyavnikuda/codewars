impl Solution {
    pub fn max_valid_splits(nums: Vec<i32>) -> i32 {
        let aa = |mut bb: i32, mut cc: i32| {
            while cc != 0 {
                let dd = bb % cc;
                bb = cc;
                cc = dd;
            }
            bb
        };
        (0..=nums.len())
            .map(|bb| {
                let cc = nums
                    .iter()
                    .enumerate()
                    .filter(|(dd, _)| *dd != bb)
                    .fold(0, |dd, (_, &ee)| aa(dd, ee));
                let mut dd = 0;
                let ee = nums
                    .iter()
                    .enumerate()
                    .filter(|(ff, _)| *ff != bb)
                    .position(|(_, &ff)| {
                        dd = aa(dd, ff);
                        dd == cc
                    })
                    .unwrap();
                let mut ff = 0;
                let gg = nums
                    .iter()
                    .enumerate()
                    .rev()
                    .filter(|(gg, _)| *gg != bb)
                    .position(|(_, &gg)| {
                        ff = aa(ff, gg);
                        ff == cc
                    })
                    .unwrap();
                let hh = nums.len() - usize::from(bb < nums.len());
                (hh - 1 - gg).saturating_sub(ee) as i32
            })
            .max()
            .unwrap()
    }
}
