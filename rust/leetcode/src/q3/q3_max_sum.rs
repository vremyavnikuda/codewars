impl Solution {
    pub fn max_sum(nums: Vec<i32>, k: i32) -> i32 {
        let mut aa = [0; 31];
        for &bb in &nums {
            for (cc, dd) in aa.iter_mut().enumerate() {
                *dd += (bb >> cc) & 1;
            }
        }
        let mut bb = 0_i64;
        for _ in 0..k {
            let mut cc = 0_i64;
            for (dd, ee) in aa.iter_mut().enumerate() {
                if *ee > 0 {
                    cc |= 1_i64 << dd;
                    *ee -= 1;
                }
            }
            bb = (bb + cc * cc) % 1_000_000_007;
        }
        bb as i32
    }
}

#[cfg(test)]
mod tests {
    use super::Solution;
    #[test]
    fn max_sum_cases() {
        assert_eq!(Solution::max_sum(vec![2, 6, 5, 8], 2), 261);
        assert_eq!(Solution::max_sum(vec![0, 0], 2), 0);
        assert_eq!(Solution::max_sum(vec![1, 2, 4], 3), 49);
        assert_eq!(Solution::max_sum(vec![1_000_000_000; 2], 2), 98);
    }
}
