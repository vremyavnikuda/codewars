use std::collections::HashMap;

struct Solution;

impl Solution {
    pub fn special_triplets(nums: Vec<i32>) -> i32 {
        let m: i64 = 1_000_000_007;

        let mut l: HashMap<i32, i64> = HashMap::new();
        let mut r: HashMap<i32, i64> = HashMap::new();

        for &n in &nums {
            *r.entry(n).or_insert(0) += 1;
        }

        let mut a = 0i64;

        for &v in &nums {
            *r.entry(v).or_insert(0) -= 1;

            let t = v * 2;
            let lc = *l.get(&t).unwrap_or(&0);
            let rc = *r.get(&t).unwrap_or(&0);

            a = (a + lc * rc % m) % m;

            *l.entry(v).or_insert(0) += 1;
        }

        a as i32
    }
}

fn main() {
    let r1 = Solution::special_triplets(vec![1, 2, 1]);
    let r2 = Solution::special_triplets(vec![2, 4, 2, 4, 2]);

    println!("{}", r1);
    println!("{}", r2);
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn t1() {
        assert_eq!(Solution::special_triplets(vec![1, 2, 1]), 1);
    }

    #[test]
    fn t2() {
        assert_eq!(Solution::special_triplets(vec![2, 4, 2, 4, 2]), 6);
    }

    #[test]
    fn t3() {
        assert_eq!(Solution::special_triplets(vec![1, 1, 1]), 0);
    }

    #[test]
    fn t4() {
        assert_eq!(Solution::special_triplets(vec![3, 6, 3, 6, 3]), 6);
    }
}
