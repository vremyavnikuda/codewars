impl Solution {
    pub fn min_operations(nums: Vec<i32>, sum: i32) -> i32 {
        let mut aa = [u16::MAX / 2; 5001];
        aa[0] = 0;

        for &bb in &nums {
            let mut cc = aa;

            std::iter::successors(Some((bb, 0_u16)), |&(dd, ee)| {
                (dd > 1).then(|| (dd / 2, ee + 1))
            })
            .chain(std::iter::successors(
                (bb <= sum / 2).then_some((bb * 2, 1_u16)),
                |&(dd, ee)| (dd <= sum / 2).then(|| (dd * 2, ee + 1)),
            ))
            .filter(|&(dd, _)| dd <= sum)
            .for_each(|(dd, ee)| {
                (0..=sum as usize - dd as usize).for_each(|ff| {
                    let gg = ff + dd as usize;
                    cc[gg] = cc[gg].min(aa[ff] + ee);
                });
            });

            aa = cc;
            if aa[sum as usize] == 0 {
                return 0;
            }
        }

        let bb = aa[sum as usize];
        (bb < u16::MAX / 2).then_some(bb as i32).unwrap_or(-1)
    }
}
