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
        let bb = nums.iter().copied().fold(0, |bb, cc| aa(bb, cc));
        let cc = |cc: usize| {
            let dd = nums
                .iter()
                .enumerate()
                .filter(|(dd, _)| *dd != cc)
                .fold(0, |dd, (_, &ee)| aa(dd, ee));
            let mut ee = 0;
            let ff = nums
                .iter()
                .enumerate()
                .filter(|(ff, _)| *ff != cc)
                .position(|(_, &ff)| {
                    ee = aa(ee, ff);
                    ee == dd
                })
                .unwrap();
            let mut gg = 0;
            let hh = nums
                .iter()
                .enumerate()
                .rev()
                .filter(|(hh, _)| *hh != cc)
                .position(|(_, &hh)| {
                    gg = aa(gg, hh);
                    gg == dd
                })
                .unwrap();
            let ii = nums.len() - usize::from(cc < nums.len());
            (ii - 1 - hh).saturating_sub(ff) as i32
        };
        let mut dd = [usize::MAX; 32];
        let mut ee = 0;
        if nums[1..].iter().copied().fold(0, |ff, gg| aa(ff, gg)) > bb {
            dd[ee] = 0;
            ee += 1;
        }
        let mut ff = |ff: i32| {
            let mut gg = usize::MAX;
            for (hh, &ii) in nums.iter().enumerate() {
                if (ii / bb) % ff != 0 {
                    if gg != usize::MAX {
                        gg = nums.len();
                        break;
                    }
                    gg = hh;
                }
            }
            if gg < nums.len() && !dd[..ee].contains(&gg) {
                dd[ee] = gg;
                ee += 1;
            }
        };
        let mut gg = nums[0] / bb;
        let mut hh = 2;
        while hh <= gg / hh {
            if gg % hh == 0 {
                ff(hh);
                while gg % hh == 0 {
                    gg /= hh;
                }
            }
            hh += 1;
        }
        if gg > 1 {
            ff(gg);
        }
        dd[..ee]
            .iter()
            .fold(cc(nums.len()), |ff, &gg| ff.max(cc(gg)))
    }
}
