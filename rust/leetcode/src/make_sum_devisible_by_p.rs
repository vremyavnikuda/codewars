use std::collections::HashMap;

struct Solution;

impl Solution {
    pub fn min_subarray(nums: Vec<i32>, p: i32) -> i32 {
        let p = p as i64;
        let t: i64 = nums.iter().map(|&x| x as i64).sum::<i64>() % p;

        if t == 0 {
            return 0;
        }

        let n = nums.len();
        let mut m: HashMap<i64, i32> = HashMap::new();
        m.insert(0, -1);

        let mut r = n as i32;
        let mut c = 0i64;

        for (i, &v) in nums.iter().enumerate() {
            c = (c + v as i64) % p;
            let q = (c - t + p) % p;

            if let Some(&j) = m.get(&q) {
                r = r.min(i as i32 - j);
            }

            m.insert(c, i as i32);
        }

        if r == n as i32 { -1 } else { r }
    }
}

fn main() {
    let r1 = Solution::min_subarray(vec![3, 1, 4, 2], 6);
    let r2 = Solution::min_subarray(vec![6, 3, 5, 2], 9);
    let r3 = Solution::min_subarray(vec![1, 2, 3], 3);

    println!("{}", r1);
    println!("{}", r2);
    println!("{}", r3);
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn t1() {
        assert_eq!(Solution::min_subarray(vec![3, 1, 4, 2], 6), 1);
    }

    #[test]
    fn t2() {
        assert_eq!(Solution::min_subarray(vec![6, 3, 5, 2], 9), 2);
    }

    #[test]
    fn t3() {
        assert_eq!(Solution::min_subarray(vec![1, 2, 3], 3), 0);
    }

    #[test]
    fn t4() {
        assert_eq!(Solution::min_subarray(vec![1, 2, 3], 7), -1);
    }

    #[test]
    fn t5() {
        assert_eq!(
            Solution::min_subarray(vec![1000000000, 1000000000, 1000000000], 3),
            0
        );
    }
}
