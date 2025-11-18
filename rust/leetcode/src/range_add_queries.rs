struct Solution;

impl Solution {
    pub fn range_add_queries(n: i32, queries: Vec<Vec<i32>>) -> Vec<Vec<i32>> {
        let n = n as usize;
        let mut matrix = vec![vec![0; n]; n];
        for query in queries.iter() {
            let row1 = query[0] as usize;
            let col1 = query[1] as usize;
            let row2 = query[2] as usize;
            let col2 = query[3] as usize;
            matrix[row1][col1] += 1;
            if row2 + 1 < n {
                matrix[row2 + 1][col1] -= 1;
            }
            if col2 + 1 < n {
                matrix[row1][col2 + 1] -= 1;
            }
            if row2 + 1 < n && col2 + 1 < n {
                matrix[row2 + 1][col2 + 1] += 1;
            }
        }
        for i in 0..n {
            for j in 0..n {
                if i > 0 {
                    matrix[i][j] += matrix[i - 1][j];
                }
                if j > 0 {
                    matrix[i][j] += matrix[i][j - 1];
                }
                if i > 0 && j > 0 {
                    matrix[i][j] -= matrix[i - 1][j - 1];
                }
            }
        }
        matrix
    }
}
