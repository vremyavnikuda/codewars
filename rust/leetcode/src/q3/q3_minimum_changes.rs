impl Solution {
    pub fn minimum_changes(s: String, k: i32) -> i32 {
        let aa = s.as_bytes();
        let bb = aa.len();
        let cc = k as usize;
        let dd = i32::MAX / 4;
        let mut ee = vec![vec![dd; bb + 1]; bb + 1];
        let mut ff = vec![vec![dd; cc + 1]; bb + 1];
        ff[0][0] = 0;
        for gg in 1..=bb {
            for hh in gg..=bb {
                let ii = hh - gg + 1;
                for jj in 1..ii {
                    if ii % jj == 0 {
                        let kk = (0..ii)
                            .map(|ll| (ll, (ii / jj - 1 - ll / jj) * jj + ll % jj))
                            .take_while(|&(ll, mm)| ll < mm)
                            .filter(|&(ll, mm)| ![aa[gg - 1 + ll]].contains(&aa[gg - 1 + mm]))
                            .count() as i32;
                        ee[gg][hh] = ee[gg][hh].min(kk);
                    }
                }
            }
        }
        for gg in 1..=bb {
            for hh in 1..=cc {
                ff[gg][hh] = (0..gg - 1)
                    .map(|ii| ff[ii][hh - 1] + ee[ii + 1][gg])
                    .fold(ff[gg][hh], i32::min);
            }
        }
        ff[bb][cc]
    }
}
