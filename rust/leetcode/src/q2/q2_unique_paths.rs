impl Solution {
    pub fn unique_paths(grid: Vec<Vec<i32>>) -> i32 {
        const AA: i32 = 1_000_000_007;
        let bb = grid[0].len();
        let mut cc = vec![(0i32, 0i32); bb + 1];
        cc[1] = (1, 1);
        for dd in &grid {
            for (ee, &ff) in dd.iter().enumerate() {
                let (gg, hh) = (cc[ee].0, cc[ee + 1].1);
                cc[ee + 1] = if ff == 1 {
                    (hh, gg)
                } else {
                    let ii = (gg + hh) % AA;
                    (ii, ii)
                };
            }
        }
        cc[bb].0
    }
}
