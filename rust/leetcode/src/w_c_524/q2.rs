impl Solution {
    pub fn last_visited_cell(grid: Vec<Vec<char>>) -> Vec<i32> {
        let (m, n) = (grid.len(), grid[0].len());
        let mut seen = vec![false; m * n];
        let (mut r, mut c) = (0usize, 0usize);
        seen[0] = true;
        loop {
            let (nr, nc) = match grid[r][c] {
                'L' => (r, c.wrapping_sub(1)),
                'R' => (r, c + 1),
                'U' => (r.wrapping_sub(1), c),
                _ => (r + 1, c),
            };
            if nr >= m || nc >= n || seen[nr * n + nc] {
                return vec![r as i32, c as i32];
            }
            seen[nr * n + nc] = true;
            r = nr;
            c = nc;
        }
    }
}
