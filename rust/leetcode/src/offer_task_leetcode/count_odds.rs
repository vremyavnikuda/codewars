struct Solution;

impl Solution {
    pub fn count_odds(low: i32, high: i32) -> i32 {
        let h = (high + 1) >> 1;
        let l = low >> 1;
        h - l
    }
}

fn main() {
    let r1 = Solution::count_odds(3, 7);
    let r2 = Solution::count_odds(8, 10);

    println!("{}", r1);
    println!("{}", r2);
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn t1() {
        assert_eq!(Solution::count_odds(3, 7), 3);
    }

    #[test]
    fn t2() {
        assert_eq!(Solution::count_odds(8, 10), 1);
    }

    #[test]
    fn t3() {
        assert_eq!(Solution::count_odds(1, 1), 1);
    }

    #[test]
    fn t4() {
        assert_eq!(Solution::count_odds(2, 2), 0);
    }
}
