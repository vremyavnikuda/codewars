impl Solution {
    pub fn min_cost(grid: Vec<Vec<i32>>) -> i32 {
        let aa = grid.len();
        let bb = grid[0].len();
        let cc = grid.iter().flatten().fold(0, |dd, &ee| dd.max(ee));
        let cc = 1usize << (32 - (cc as u32).leading_zeros());
        let dd = |ee: usize, ff: usize, gg: usize| (ee * bb + ff) * cc + gg;
        let mut asd = vec![false; aa * bb * cc];
        asd[dd(0, 0, grid[0][0] as usize)] = true;
        for ee in 0..aa {
            for ff in 0..bb {
                let gg = grid[ee][ff] as usize;
                if ee > 0 || ff > 0 {
                    for hh in 0..cc {
                        let ii = hh ^ gg;
                        if (ee > 0 && asd[dd(ee - 1, ff, ii)])
                            || (ff > 0 && asd[dd(ee, ff - 1, ii)])
                        {
                            asd[dd(ee, ff, hh)] = true;
                        }
                    }
                }
            }
        }
        (0..cc).find(|&jj| asd[dd(aa - 1, bb - 1, jj)]).unwrap() as i32
    }
}
