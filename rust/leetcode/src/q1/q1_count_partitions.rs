use std::collections::BTreeMap;

struct Solution;

impl Solution {
    pub fn count_partitions(nums: Vec<i32>, k: i32) -> i32 {
        let m: i64 = 1_000_000_007;

        let n = nums.len();
        let mut s: BTreeMap<i32, i32> = BTreeMap::new();
        let mut f = vec![0i64; n + 1];
        let mut g = vec![0i64; n + 1];

        f[0] = 1;
        g[0] = 1;
        let mut l = 1usize;

        for r in 1..=n {
            let x = nums[r - 1];
            *s.entry(x).or_insert(0) += 1;

            while *s.iter().next_back().unwrap().0 - *s.iter().next().unwrap().0 > k {
                let v = nums[l - 1];
                if let Some(c) = s.get_mut(&v) {
                    *c -= 1;
                    if *c == 0 {
                        s.remove(&v);
                    }
                }
                l += 1;
            }

            f[r] = (g[r - 1] - if l >= 2 { g[l - 2] } else { 0 } + m) % m;
            g[r] = (g[r - 1] + f[r]) % m;
        }

        f[n] as i32
    }
}

fn main() {
    let r1 = Solution::count_partitions(vec![2, 3, 3, 1], 2);
    let r2 = Solution::count_partitions(vec![1, 2, 3], 1);

    println!("{}", r1);
    println!("{}", r2);
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn t1() {
        assert_eq!(Solution::count_partitions(vec![2, 3, 3, 1], 2), 4);
    }

    #[test]
    fn t2() {
        assert_eq!(Solution::count_partitions(vec![1, 2, 3], 1), 2);
    }

    #[test]
    fn t3() {
        assert_eq!(Solution::count_partitions(vec![1, 1, 1, 1], 0), 8);
    }

    #[test]
    fn t4() {
        assert_eq!(Solution::count_partitions(vec![1, 5, 3, 2, 4], 2), 2);
    }
}
