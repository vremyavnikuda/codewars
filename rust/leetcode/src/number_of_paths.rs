struct Solution;

impl Solution {
    pub fn number_of_paths(grid: Vec<Vec<i32>>, k: i32) -> i32 {
        const M: i32 = 1_000_000_007;
        let r = grid.len();
        let c = grid[0].len();
        let k = k as usize;
        let mut d = vec![vec![vec![-1; k]; c]; r];

        fn f(
            grid: &Vec<Vec<i32>>,
            d: &mut Vec<Vec<Vec<i32>>>,
            r: usize,
            c: usize,
            k: usize,
            i: usize,
            j: usize,
            s: usize,
        ) -> i32 {
            if i >= r || j >= c {
                return 0;
            }

            let ns = (s + grid[i][j] as usize) % k;

            if i == r - 1 && j == c - 1 {
                return if ns == 0 { 1 } else { 0 };
            }

            if d[i][j][ns] != -1 {
                return d[i][j][ns];
            }

            let mut p = 0i64;
            p += f(grid, d, r, c, k, i + 1, j, ns) as i64;
            p += f(grid, d, r, c, k, i, j + 1, ns) as i64;
            p %= 1_000_000_007;

            d[i][j][ns] = p as i32;
            p as i32
        }

        f(&grid, &mut d, r, c, k, 0, 0, 0)
    }
}

fn main() {
    let g1 = vec![vec![5, 2, 4], vec![3, 0, 5], vec![0, 7, 2]];
    let g2 = vec![vec![0, 0]];

    println!("grid1, k=5: {}", Solution::number_of_paths(g1, 5));
    println!("grid2, k=5: {}", Solution::number_of_paths(g2, 5));
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn t1() {
        let g = vec![vec![5, 2, 4], vec![3, 0, 5], vec![0, 7, 2]];
        assert_eq!(Solution::number_of_paths(g, 5), 2);
    }

    #[test]
    fn t2() {
        let g = vec![vec![0, 0]];
        assert_eq!(Solution::number_of_paths(g, 5), 1);
    }

    #[test]
    fn t3() {
        let g = vec![vec![7, 3, 4, 9], vec![2, 3, 6, 2], vec![2, 3, 7, 0]];
        assert_eq!(Solution::number_of_paths(g, 1), 10);
    }
}
