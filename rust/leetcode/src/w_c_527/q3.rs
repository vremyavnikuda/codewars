impl Solution {
    pub fn min_cost(n: i32, colors: String, edges: Vec<Vec<i32>>) -> i64 {
        let n = n as usize;
        let mut adj = vec![vec![]; n];
        for e in &edges {
            adj[e[0] as usize].push(e[1] as usize);
            adj[e[1] as usize].push(e[0] as usize);
        }
        let mut parent = vec![usize::MAX; n];
        let mut order = vec![0];
        parent[0] = 0;
        for k in 0..n {
            let v = order[k];
            for &u in &adj[v] {
                if parent[u] == usize::MAX {
                    parent[u] = v;
                    order.push(u);
                }
            }
        }
        let mut size = vec![1i64; n];
        for &v in order.iter().skip(1).rev() {
            size[parent[v]] += size[v];
        }
        let c = colors.as_bytes();
        let mut red_total = 0;
        let mut dp = vec![0i64; n];
        for v in 0..n {
            if c[v] == b'R' {
                red_total += size[v];
                dp[v] = -size[v];
            } else {
                dp[v] = size[v];
            }
        }
        let mut best = 0;
        for &v in order.iter().rev() {
            best = best.min(dp[v]);
            if v != 0 && dp[v] < 0 {
                dp[parent[v]] += dp[v];
            }
        }
        red_total + best
    }
}
