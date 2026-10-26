impl Solution {
    pub fn count_islands(mut grid: Vec<Vec<i32>>, k: i32) -> i32 {
        let aa = grid.len();
        let bb = grid[0].len();
        fn cc(dd: &mut [Vec<i32>], ee: usize, ff: usize, aa: usize, bb: usize) -> i64 {
            let mut gg = dd[ee][ff] as i64;
            dd[ee][ff] = 0;
            for (hh, ii) in [(-1_isize, 0), (0, 1), (1, 0), (0, -1)] {
                let jj = ee as isize + hh;
                let kk = ff as isize + ii;
                if jj >= 0 && kk >= 0 {
                    let (jj, kk) = (jj as usize, kk as usize);
                    if jj < aa && kk < bb && dd[jj][kk] != 0 {
                        gg += cc(dd, jj, kk, aa, bb);
                    }
                }
            }
            gg
        }
        (0..aa)
            .flat_map(|dd| (0..bb).map(move |ee| (dd, ee)))
            .fold(0, |asd, (dd, ee)| {
                asd + if grid[dd][ee] != 0 {
                    (cc(&mut grid, dd, ee, aa, bb) % k as i64 == 0) as i32
                } else {
                    0
                }
            })
    }
}
