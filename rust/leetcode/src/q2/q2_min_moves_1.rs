impl Solution {
    pub fn min_moves(nums: Vec<i32>) -> i32 {
        let (aa, bb) = nums
            .iter()
            .fold((0i64, i32::MAX), |(cc, dd), &ee| (cc + ee as i64, dd.min(ee)));
        (aa - bb as i64 * nums.len() as i64) as i32
    }
}

#[cfg(test)]
mod tests {
    use super::*;
    #[test]
    fn examples() {
        assert_eq!(Solution::min_moves(vec![1, 2, 3]), 3);
        assert_eq!(Solution::min_moves(vec![1, 1, 1]), 0);
        assert_eq!(Solution::min_moves(vec![-1_000_000_000, 1_000_000_000]), 2_000_000_000);
    }
}
