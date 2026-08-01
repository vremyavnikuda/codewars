struct Solution;

impl Solution {
    pub fn max_profit(prices: Vec<i32>, strategy: Vec<i32>, k: i32) -> i64 {
        let n = prices.len();
        let mut s = vec![0i64; n + 1];
        let mut t = vec![0i64; n + 1];

        for i in 1..=n {
            let a = prices[i - 1] as i64;
            let b = strategy[i - 1] as i64;
            s[i] = s[i - 1] + a * b;
            t[i] = t[i - 1] + a;
        }

        let mut r = s[n];
        let k = k as usize;

        for i in k..=n {
            r = r.max(s[n] - (s[i] - s[i - k]) + (t[i] - t[i - k / 2]));
        }

        r
    }
}

fn main() {
    let r1 = Solution::max_profit(vec![10, 20, 30, 40], vec![1, -1, 1, -1], 2);
    let r2 = Solution::max_profit(vec![5, 10, 15], vec![1, 1, 1], 1);

    println!("{}", r1);
    println!("{}", r2);
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn t1() {
        assert_eq!(
            Solution::max_profit(vec![10, 20, 30, 40], vec![1, -1, 1, -1], 2),
            60
        );
    }

    #[test]
    fn t2() {
        assert_eq!(Solution::max_profit(vec![5, 10, 15], vec![1, 1, 1], 1), 30);
    }

    #[test]
    fn t3() {
        assert_eq!(
            Solution::max_profit(vec![1, 2, 3, 4, 5], vec![1, 1, 1, 1, 1], 3),
            15
        );
    }
}
