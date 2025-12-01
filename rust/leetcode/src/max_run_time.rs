struct Solution;

impl Solution {
    pub fn max_run_time(n: i32, batteries: Vec<i32>) -> i64 {
        let n = n as i64;
        let mut l = 0i64;
        let mut r: i64 = batteries.iter().map(|&x| x as i64).sum();

        while l < r {
            let m = (l + r + 1) >> 1;
            let s: i64 = batteries.iter().map(|&x| (x as i64).min(m)).sum();

            if s >= n * m {
                l = m;
            } else {
                r = m - 1;
            }
        }

        l
    }
}

fn main() {
    let r1 = Solution::max_run_time(2, vec![3, 3, 3]);
    let r2 = Solution::max_run_time(2, vec![1, 1, 1, 1]);

    println!("{}", r1);
    println!("{}", r2);
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn t1() {
        assert_eq!(Solution::max_run_time(2, vec![3, 3, 3]), 4);
    }

    #[test]
    fn t2() {
        assert_eq!(Solution::max_run_time(2, vec![1, 1, 1, 1]), 2);
    }

    #[test]
    fn t3() {
        assert_eq!(Solution::max_run_time(3, vec![10, 10, 3, 5]), 8);
    }
}
