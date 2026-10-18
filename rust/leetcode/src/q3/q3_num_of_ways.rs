impl Solution {
    pub fn num_of_ways(nums: Vec<i32>) -> i32 {
        let aa = 1_000_000_007_i64;
        let mut bb = 1_i64;
        let mut cc = 1_i64;
        for (dd, &ee) in nums.iter().enumerate() {
            let (ff, gg) = nums[..dd]
                .iter()
                .fold((i64::MIN, i64::MAX), |(ff, gg), &hh| {
                    if hh < ee {
                        (ff.max(i64::from(hh)), gg)
                    } else {
                        (ff, gg.min(i64::from(hh)))
                    }
                });
            let hh = 1 + nums[dd + 1..]
                .iter()
                .filter(|&&ii| ff < i64::from(ii) && i64::from(ii) < gg)
                .count();
            bb = bb * (dd + 1) as i64 % aa;
            cc = cc * hh as i64 % aa;
        }
        let mut dd = aa - 2;
        while dd > 0 {
            if dd & 1 != 0 {
                bb = bb * cc % aa;
            }
            cc = cc * cc % aa;
            dd >>= 1;
        }
        ((bb + aa - 1) % aa) as i32
    }
}

#[cfg(test)]
mod tests {
    use super::*;
    #[test]
    fn counts_reorderings() {
        assert_eq!(Solution::num_of_ways(vec![2, 1, 3]), 1);
        assert_eq!(Solution::num_of_ways(vec![3, 4, 5, 1, 2]), 5);
        assert_eq!(Solution::num_of_ways(vec![3, 1, 2, 5, 4, 6]), 19);
        assert_eq!(Solution::num_of_ways(vec![0, i32::MIN, i32::MAX]), 1);
        assert_eq!(Solution::num_of_ways(vec![1]), 0);
        assert_eq!(Solution::num_of_ways((1..=1000).collect()), 0);
        assert_eq!(Solution::num_of_ways((1..=1000).rev().collect()), 0);
    }
}
