struct Solution;

impl Solution {
    pub fn get_descent_periods(prices: Vec<i32>) -> i64 {
        let (mut a, mut c) = (0i64, 1i64);

        for w in prices.windows(2) {
            c = if w[0] - w[1] == 1 { c + 1 } else { 1 };
            a += c;
        }

        a + 1
    }
}

fn main() {
    let r1 = Solution::get_descent_periods(vec![3, 2, 1, 4]);
    let r2 = Solution::get_descent_periods(vec![8, 6, 7, 7]);
    let r3 = Solution::get_descent_periods(vec![1]);

    println!("{}", r1);
    println!("{}", r2);
    println!("{}", r3);
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn t1() {
        assert_eq!(Solution::get_descent_periods(vec![3, 2, 1, 4]), 7);
    }

    #[test]
    fn t2() {
        assert_eq!(Solution::get_descent_periods(vec![8, 6, 7, 7]), 4);
    }

    #[test]
    fn t3() {
        assert_eq!(Solution::get_descent_periods(vec![1]), 1);
    }

    #[test]
    fn t4() {
        assert_eq!(Solution::get_descent_periods(vec![5, 4, 3, 2, 1]), 15);
    }
}
