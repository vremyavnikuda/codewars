impl Solution {
    pub fn count_servers(n: i32, mut logs: Vec<Vec<i32>>, x: i32, queries: Vec<i32>) -> Vec<i32> {
        logs.sort_unstable_by_key(|aa| aa[1]);
        let mut aa: Vec<(i32, usize)> = queries
            .into_iter()
            .enumerate()
            .map(|(bb, cc)| (cc, bb))
            .collect();
        aa.sort_unstable();
        let mut bb = vec![0i32; n as usize + 1];
        let mut cc = vec![0i32; aa.len()];
        let mut dd = 0usize;
        let mut ee = 0usize;
        let mut ff = 0i32;
        for (gg, hh) in aa {
            while dd < logs.len() && logs[dd][1] <= gg {
                let ii = logs[dd][0] as usize;
                if bb[ii] == 0 {
                    ff += 1;
                }
                bb[ii] += 1;
                dd += 1;
            }
            let jj = gg - x;
            while ee < logs.len() && logs[ee][1] < jj {
                let ii = logs[ee][0] as usize;
                bb[ii] -= 1;
                if bb[ii] == 0 {
                    ff -= 1;
                }
                ee += 1;
            }
            cc[hh] = n - ff;
        }
        cc
    }
}
