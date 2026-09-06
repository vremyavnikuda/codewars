impl Solution {
    pub fn min_cost(grid: Vec<Vec<i32>>, k: i32) -> i32 {
        let aa = grid.len();
        let bb = grid[0].len();
        let cc = aa * bb;
        let mut dd = [[i32::MAX; 75 * 75]; 4];
        for ee in 0..4 {
            dd[ee][0] = grid[0][0];
        }
        for ff in 0..=k {
            for gg in 0..4 {
                let hh = if gg < 2 { 1isize } else { bb as isize } * if gg % 2 == 0 { 1 } else { -1 };
                for ii in 0..cc {
                    let jj = if gg % 2 == 0 { ii } else { cc - 1 - ii };
                    let kk = jj as isize - hh;
                    if kk < 0 || kk >= cc as isize || (gg < 2 && kk as usize / bb != jj / bb) {
                        continue;
                    }
                    let ll = dd[gg][kk as usize].saturating_add(grid[jj / bb][jj % bb]);
                    if ll < dd[gg][jj] {
                        dd[gg][jj] = ll;
                    }
                }
            }
            if ff < k {
                for ii in 0..cc {
                    let mm = (0..4).map(|nn| dd[nn][ii]).min().unwrap();
                    for nn in 0..4 {
                        dd[nn][ii] = mm;
                    }
                }
            }
        }
        let oo = (0..4).map(|pp| dd[pp][cc - 1]).min().unwrap();
        if oo == i32::MAX { -1 } else { oo }
    }
}
