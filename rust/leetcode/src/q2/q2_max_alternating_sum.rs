impl Solution {
    pub fn max_alternating_sum(nums: Vec<i32>) -> i64 {
        let mut aa = nums;
        let bb = aa.len() / 2;
        if bb > 0 {
            aa.select_nth_unstable_by_key(bb, |cc| cc.unsigned_abs());
        }
        aa.iter().enumerate().fold(0, |cc, (dd, &ee)| {
            let ff = i64::from(ee).pow(2);
            cc + if dd < bb { -ff } else { ff }
        })
    }
}

#[cfg(test)]
mod tests {
    use super::*;
    #[test]
    fn squared_partition() {
        assert_eq!(Solution::max_alternating_sum(vec![1, 2, 3, 4]), 20);
        assert_eq!(Solution::max_alternating_sum(vec![-3, 1, -2]), 12);
        assert_eq!(Solution::max_alternating_sum(vec![-2, 2, -2, 2]), 0);
        assert_eq!(Solution::max_alternating_sum(vec![0, 0, 0]), 0);
        assert_eq!(
            Solution::max_alternating_sum(vec![i32::MIN]),
            4_611_686_018_427_387_904
        );
        assert_eq!(Solution::max_alternating_sum(vec![]), 0);
    }
}
