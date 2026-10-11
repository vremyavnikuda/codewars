impl Solution {
    pub fn sum_of_squares(nums: Vec<i32>) -> i32 {
        let aa = nums.len();
        nums.iter()
            .enumerate()
            .filter(|&(bb, _)| aa % (bb + 1) == 0)
            .map(|(_, &cc)| cc * cc)
            .sum()
    }
}

#[cfg(test)]
mod tests {
    use super::Solution;

    #[test]
    fn aa() {
        assert_eq!(Solution::sum_of_squares(vec![1, 2, 3, 4]), 21);
        assert_eq!(Solution::sum_of_squares(vec![2, 7, 1, 19, 18, 3]), 63);
        assert_eq!(Solution::sum_of_squares(vec![3]), 9);
        assert_eq!(Solution::sum_of_squares(vec![]), 0);
        assert_eq!(Solution::sum_of_squares(vec![-1, -2, -3, -4]), 21);
    }
}
