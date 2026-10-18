impl Solution {
    pub fn find_colored_root(edges: Vec<Vec<i32>>, colors: String) -> i32 {
        let col: Vec<u8> = colors
            .bytes()
            .map(|b| match b {
                b'R' => 0,
                b'B' => 1,
                _ => 2,
            })
            .collect();
        let n = col.len();
        let mut indeg = vec![0u8; n];
        let mut deg = vec![0u8; n];
        for e in &edges {
            let (u, v) = (e[0] as usize, e[1] as usize);
            let child = if (col[u] + 1) % 3 == col[v] {
                v
            } else if (col[v] + 1) % 3 == col[u] {
                u
            } else {
                return -1;
            };
            indeg[child] += 1;
            if indeg[child] > 1 {
                return -1;
            }
            deg[u] += 1;
            deg[v] += 1;
        }
        let root = indeg.iter().position(|&d| d == 0).unwrap();
        if deg[root] <= 2 { root as i32 } else { -1 }
    }
}
