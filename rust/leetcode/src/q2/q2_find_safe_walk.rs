use std::collections::VecDeque;

impl Solution {
    pub fn find_safe_walk(grid: Vec<Vec<i32>>, health: i32) -> bool {
        let q1 = grid.len();
        let q2 = grid[0].len();
        let mut q3 = vec![vec![i32::MAX; q2]; q1];
        let mut q4: VecDeque<(usize, usize)> = VecDeque::new();
        q3[0][0] = grid[0][0];
        q4.push_back((0, 0));
        let q5 = [-1i32, 0, 1, 0, -1];
        while let Some((q6, q7)) = q4.pop_front() {
            for q8 in 0..4 {
                let q9 = q6 as i32 + q5[q8];
                let q10 = q7 as i32 + q5[q8 + 1];
                if q9 >= 0 && q9 < q1 as i32 && q10 >= 0 && q10 < q2 as i32 {
                    let q9 = q9 as usize;
                    let q10 = q10 as usize;
                    let q11 = q3[q6][q7] + grid[q9][q10];
                    if q3[q9][q10] > q11 {
                        q3[q9][q10] = q11;
                        q4.push_back((q9, q10));
                    }
                }
            }
        }
        q3[q1 - 1][q2 - 1] < health
    }
}
