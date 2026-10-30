use std::cmp::Reverse;
use std::collections::BinaryHeap;

impl Solution {
    pub fn shortest_path(n: i32, edges: Vec<Vec<i32>>, labels: String, k: i32) -> i32 {
        let aa = n as usize;
        let bb = k as usize;
        let cc = labels.as_bytes();
        let mut dd = vec![vec![]; aa];
        for ee in &edges {
            dd[ee[0] as usize].push((ee[1] as usize, ee[2]));
        }
        let mut ff = vec![vec![i32::MAX; bb + 1]; aa];
        ff[0][1] = 0;
        let mut gg: BinaryHeap<Reverse<(i32, usize, usize)>> = BinaryHeap::new();
        gg.push(Reverse((0, 0, 1)));
        while let Some(Reverse((hh, ii, jj))) = gg.pop() {
            if ii == aa - 1 {
                return hh;
            }
            if hh > ff[ii][jj] {
                continue;
            }
            for &(kk, ll) in &dd[ii] {
                let mm = if cc[kk] != cc[ii] { 1 } else { jj + 1 };
                let nn = hh + ll;
                if mm <= bb && nn < ff[kk][mm] {
                    ff[kk][mm] = nn;
                    gg.push(Reverse((nn, kk, mm)));
                }
            }
        }
        -1
    }
}
