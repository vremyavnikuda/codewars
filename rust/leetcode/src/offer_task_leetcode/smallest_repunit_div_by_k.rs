struct Solution;

impl Solution {
    pub fn smallest_repunit_div_by_k(k: i32) -> i32 {
        let mut r = 1 % k;

        for l in 1..=k {
            if r == 0 {
                return l;
            }
            r = (r * 10 + 1) % k;
        }

        -1
    }
}

fn main() {
    let t1 = Solution::smallest_repunit_div_by_k(1);
    let t2 = Solution::smallest_repunit_div_by_k(2);
    let t3 = Solution::smallest_repunit_div_by_k(3);

    println!("k=1: {}", t1);
    println!("k=2: {}", t2);
    println!("k=3: {}", t3);
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn t1() {
        assert_eq!(Solution::smallest_repunit_div_by_k(1), 1);
    }

    #[test]
    fn t2() {
        assert_eq!(Solution::smallest_repunit_div_by_k(2), -1);
    }

    #[test]
    fn t3() {
        assert_eq!(Solution::smallest_repunit_div_by_k(3), 3);
    }

    #[test]
    fn t7() {
        assert_eq!(Solution::smallest_repunit_div_by_k(7), 6);
    }
}
