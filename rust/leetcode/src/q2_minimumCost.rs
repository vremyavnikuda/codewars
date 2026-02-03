struct Solution;

impl Solution {
    pub fn minimum_cost(
        source: String,
        target: String,
        original: Vec<char>,
        changed: Vec<char>,
        cost: Vec<i32>,
    ) -> i64 {
        const INF: i64 = i64::MAX / 4;
        let mut g = [[INF; 26]; 26];
        for i in 0..26 {
            g[i][i] = 0;
        }

        let m = original.len();
        for i in 0..m {
            let x = (original[i] as u32 - 'a' as u32) as usize;
            let y = (changed[i] as u32 - 'a' as u32) as usize;
            let z = cost[i] as i64;
            if z < g[x][y] {
                g[x][y] = z;
            }
        }

        for k in 0..26 {
            for i in 0..26 {
                let ik = g[i][k];
                if ik == INF {
                    continue;
                }
                for j in 0..26 {
                    let kj = g[k][j];
                    if kj == INF {
                        continue;
                    }
                    let via = ik + kj;
                    if via < g[i][j] {
                        g[i][j] = via;
                    }
                }
            }
        }

        if source.len() != target.len() {
            return -1;
        }

        let s = source.as_bytes();
        let t = target.as_bytes();
        let mut ans: i64 = 0;
        for i in 0..s.len() {
            let x = (s[i] - b'a') as usize;
            let y = (t[i] - b'a') as usize;
            if x != y {
                let d = g[x][y];
                if d == INF {
                    return -1;
                }
                ans += d;
            }
        }
        ans
    }
}
