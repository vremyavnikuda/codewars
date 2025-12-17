struct Solution;

impl Solution {
    pub fn maximum_profit(prices: Vec<i32>, k: i32) -> i64 {
        let n = prices.len();
        let k = k as usize;

        let mut f = vec![vec![vec![0i64; 3]; k + 1]; n];

        for j in 1..=k {
            f[0][j][1] = -(prices[0] as i64);
            f[0][j][2] = prices[0] as i64;
        }

        for i in 1..n {
            let p = prices[i] as i64;
            for j in 1..=k {
                f[i][j][0] = f[i - 1][j][0]
                    .max(f[i - 1][j][1] + p)
                    .max(f[i - 1][j][2] - p);
                f[i][j][1] = f[i - 1][j][1].max(f[i - 1][j - 1][0] - p);
                f[i][j][2] = f[i - 1][j][2].max(f[i - 1][j - 1][0] + p);
            }
        }

        f[n - 1][k][0]
    }
}

fn main() {
    let r1 = Solution::maximum_profit(vec![1, 7, 9, 8, 2], 2);
    let r2 = Solution::maximum_profit(vec![1, 2, 3], 1);

    println!("{}", r1);
    println!("{}", r2);
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn t1() {
        assert_eq!(Solution::maximum_profit(vec![1, 7, 9, 8, 2], 2), 14);
    }

    #[test]
    fn t2() {
        assert_eq!(Solution::maximum_profit(vec![1, 2, 3], 1), 2);
    }

    #[test]
    fn t3() {
        assert_eq!(Solution::maximum_profit(vec![5, 4, 3, 2, 1], 1), 4);
    }

    #[test]
    fn t4() {
        assert_eq!(Solution::maximum_profit(vec![1, 5, 2, 8, 3, 10], 2), 17);
    }
}
