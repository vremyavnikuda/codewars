impl Solution {
    pub fn closed_island(mut grid: Vec<Vec<i32>>) -> i32 {
        let aa = grid.len();
        let bb = grid[0].len();
        fn cc(dd: &mut [Vec<i32>], ee: usize, ff: usize, aa: usize, bb: usize) -> i32 {
            let mut gg = (ee > 0 && ee + 1 < aa && ff > 0 && ff + 1 < bb) as i32;
            dd[ee][ff] = 1;
            for (hh, ii) in [(-1_isize, 0), (0, 1), (1, 0), (0, -1)] {
                let jj = ee as isize + hh;
                let kk = ff as isize + ii;
                if jj >= 0 && kk >= 0 {
                    let (jj, kk) = (jj as usize, kk as usize);
                    if jj < aa && kk < bb && dd[jj][kk] == 0 {
                        gg &= cc(dd, jj, kk, aa, bb);
                    }
                }
            }
            gg
        }
        (0..aa)
            .flat_map(|dd| (0..bb).map(move |ee| (dd, ee)))
            .fold(0, |asd, (dd, ee)| {
                asd + if grid[dd][ee] == 0 {
                    cc(&mut grid, dd, ee, aa, bb)
                } else {
                    0
                }
            })
    }
}
