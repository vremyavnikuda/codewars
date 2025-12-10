struct Solution;

impl Solution {
    pub fn count_permutations(complexity: Vec<i32>) -> i32 {
        let m = 1_000_000_007i64;
        let mut r = 1i64;

        for i in 1..complexity.len() {
            if complexity[i] <= complexity[0] {
                return 0;
            }
            r = (r * i as i64) % m;
        }

        r as i32
    }
}

fn main() {
    let r1 = Solution::count_permutations(vec![1, 2, 3, 4]);
    let r2 = Solution::count_permutations(vec![5, 3, 4, 6]);

    println!("{}", r1);
    println!("{}", r2);
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn t1() {
        assert_eq!(Solution::count_permutations(vec![1, 2, 3, 4]), 6);
    }

    #[test]
    fn t2() {
        assert_eq!(Solution::count_permutations(vec![5, 3, 4, 6]), 0);
    }

    #[test]
    fn t3() {
        assert_eq!(Solution::count_permutations(vec![1, 2]), 1);
    }

    #[test]
    fn t4() {
        assert_eq!(Solution::count_permutations(vec![1, 3, 2, 4]), 0);
    }
}
