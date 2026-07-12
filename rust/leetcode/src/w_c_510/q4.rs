impl Solution {
    pub fn max_consistent_columns(grid: Vec<Vec<i32>>, limit: i32) -> i32 {
        let q1 = grid.len();
        let q2 = grid[0].len();
        let mut q3 = vec![1i32; q2];
        for a1 in 0..q2 {
            for a2 in 0..a1 {
                if q3[a2] + 1 > q3[a1]
                    && (0..q1).all(|a3| (grid[a3][a1] - grid[a3][a2]).abs() <= limit)
                {
                    q3[a1] = q3[a2] + 1;
                }
            }
        }
        q3.into_iter().max().unwrap()
    }
}
