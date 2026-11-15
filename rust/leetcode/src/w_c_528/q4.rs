impl Solution {
    pub fn count_consistent(nums: Vec<i32>) -> i64 {
        let aa = *nums.iter().max().unwrap() as usize;
        let mut bb = vec![-1i32; aa + 1];
        let mut cc: Vec<(i32, i32)> = Vec::new();
        let mut gg: Vec<(i32, i32)> = Vec::new();
        let mut dd = 0i64;
        for ee in 0..nums.len() {
            let ff = nums[ee];
            bb[ff as usize] = ee as i32;
            gg.clear();
            for &(hh, ii) in &cc {
                let jj = hh & ff;
                if gg.last().is_some_and(|&(kk, _)| kk == jj) {
                    continue;
                }
                gg.push((jj, ii));
            }
            if !gg.last().is_some_and(|&(kk, _)| kk == ff) {
                gg.push((ff, ee as i32));
            }
            std::mem::swap(&mut cc, &mut gg);
            for pp in 0..cc.len() {
                let (qq, rr) = cc[pp];
                let ss = if pp + 1 < cc.len() {
                    cc[pp + 1].1 - 1
                } else {
                    ee as i32
                };
                let tt = bb[qq as usize];
                if tt >= rr {
                    dd += (ss.min(tt) - rr + 1) as i64;
                }
            }
        }
        dd
    }
}
