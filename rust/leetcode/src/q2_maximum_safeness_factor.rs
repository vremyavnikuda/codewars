use std::collections::VecDeque;

impl Solution {
    pub fn maximum_safeness_factor(grid: Vec<Vec<i32>>) -> i32 {
        let n = grid.len();
        if grid[0][0] != 0 || grid[n - 1][n - 1] != 0 {
            return 0;
        }

        let mut q1 = VecDeque::new();
        let mut q2 = vec![vec![i32::MAX; n]; n];

        for i in 0..n {
            for j in 0..n {
                if grid[i][j] != 0 {
                    q2[i][j] = 0;
                    q1.push_back((i, j));
                }
            }
        }

        let q3 = [-1, 0, 1, 0, -1];
        while let Some((i, j)) = q1.pop_front() {
            for k in 0..4 {
                let x = i as i32 + q3[k];
                let y = j as i32 + q3[k + 1];
                if x >= 0 && x < n as i32 && y >= 0 && y < n as i32 {
                    let x = x as usize;
                    let y = y as usize;
                    if q2[x][y] == i32::MAX {
                        q2[x][y] = q2[i][j] + 1;
                        q1.push_back((x, y));
                    }
                }
            }
        }

        let mut q4: Vec<(i32, usize, usize)> = Vec::with_capacity(n * n);
        for i in 0..n {
            for j in 0..n {
                q4.push((q2[i][j], i, j));
            }
        }
        q4.sort_unstable_by(|a, b| b.0.cmp(&a.0));

        let mut q5: Vec<usize> = (0..n * n).collect();
        let mut q6 = n * n;

        fn q7(q5: &mut [usize], mut x: usize) -> usize {
            let y = {
                let mut z = x;
                while q5[z] != z {
                    z = q5[z];
                }
                z
            };
            while q5[x] != y {
                let z = q5[x];
                q5[x] = y;
                x = z;
            }
            y
        }

        fn q8(q5: &mut [usize], q6: &mut usize, a: usize, b: usize) -> bool {
            let pa = q7(q5, a);
            let pb = q7(q5, b);
            if pa == pb {
                return false;
            }
            q5[pa] = pb;
            *q6 -= 1;
            true
        }

        for &(d, i, j) in &q4 {
            for k in 0..4 {
                let x = i as i32 + q3[k];
                let y = j as i32 + q3[k + 1];
                if x >= 0 && x < n as i32 && y >= 0 && y < n as i32 {
                    let x = x as usize;
                    let y = y as usize;
                    if q2[x][y] >= d {
                        q8(&mut q5, &mut q6, i * n + j, x * n + y);
                    }
                }
            }
            if q7(&mut q5, 0) == q7(&mut q5, n * n - 1) {
                return d;
            }
        }

        0
    }
}
