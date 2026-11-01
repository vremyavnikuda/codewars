impl Solution {
    pub fn min_activation_cost(edges: Vec<Vec<i32>>, values: Vec<i32>) -> i32 {
        const INF: i64 = i64::MAX / 4;
        let n = values.len();
        let bit: Vec<usize> = values
            .iter()
            .map(|v| (v.count_ones() & 1) as usize)
            .collect();
        let mut adj = vec![vec![]; n];
        for e in &edges {
            let (u, v, c) = (e[0] as usize, e[1] as usize, e[2] as i64);
            adj[u].push((v, c));
            adj[v].push((u, c));
        }
        let mut parent = vec![(usize::MAX, 0i64); n];
        let mut order = vec![0];
        let mut seen = vec![false; n];
        seen[0] = true;
        for i in 0..n {
            let u = order[i];
            for &(v, c) in &adj[u] {
                if !seen[v] {
                    seen[v] = true;
                    parent[v] = (u, c);
                    order.push(v);
                }
            }
        }
        let mut down = vec![[INF; 2]; n];
        for x in 0..n {
            down[x][bit[x]] = 0;
        }
        let mut ans = INF;
        for &c in order.iter().skip(1).rev() {
            let (x, e) = parent[c];
            for p in 0..2 {
                ans = ans.min(down[x][p] + down[c][p] + e);
            }
            for q in 0..2 {
                let p = q ^ bit[x];
                down[x][p] = down[x][p].min(down[c][q] + e);
            }
        }
        if ans >= INF { -1 } else { ans as i32 }
    }
}

#[cfg(test)]
mod tests {
    use super::*;
    #[test]
    fn examples() {
        let e = |v: &[[i32; 3]]| v.iter().map(|a| a.to_vec()).collect::<Vec<_>>();
        assert_eq!(
            Solution::min_activation_cost(
                e(&[[0, 1, 4], [0, 2, 6], [0, 3, 3], [3, 4, 5]]),
                vec![3, 1, 7, 1, 3]
            ),
            7
        );
        assert_eq!(
            Solution::min_activation_cost(e(&[[0, 1, 5], [1, 2, 10]]), vec![1, 7, 3]),
            5
        );
        assert_eq!(
            Solution::min_activation_cost(e(&[[0, 1, 5], [0, 2, 7], [0, 3, 9]]), vec![1, 3, 5, 9]),
            -1
        );
    }
}
