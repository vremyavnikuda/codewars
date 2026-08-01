struct Solution;

impl Solution {
    pub fn find_max_consecutive_ones(nums: Vec<i32>) -> i32 {
        let mut m = 0;
        let mut c = 0;

        for &n in &nums {
            if n == 1 {
                c += 1;
                m = m.max(c);
            } else {
                c = 0;
            }
        }

        m
    }
}

fn main() {
    let r1 = Solution::find_max_consecutive_ones(vec![1, 1, 0, 1, 1, 1]);
    let r2 = Solution::find_max_consecutive_ones(vec![1, 0, 1, 1, 0, 1]);

    println!("{}", r1);
    println!("{}", r2);
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn t1() {
        assert_eq!(
            Solution::find_max_consecutive_ones(vec![1, 1, 0, 1, 1, 1]),
            3
        );
    }

    #[test]
    fn t2() {
        assert_eq!(
            Solution::find_max_consecutive_ones(vec![1, 0, 1, 1, 0, 1]),
            2
        );
    }

    #[test]
    fn t3() {
        assert_eq!(Solution::find_max_consecutive_ones(vec![1, 1, 1, 1, 1]), 5);
    }

    #[test]
    fn t4() {
        assert_eq!(Solution::find_max_consecutive_ones(vec![0, 0, 0]), 0);
    }
}
