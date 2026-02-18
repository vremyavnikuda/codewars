pub struct Solution;

impl Solution {
    #[inline(always)]
    fn fold_adjacent_bits(n: u32) -> u32 {
        n ^ (n >> 1)
    }

    #[inline(always)]
    fn is_all_ones(x: u32) -> bool {
        (x & x.wrapping_add(1)) == 0
    }

    pub fn has_alternating_bits(n: i32) -> bool {
        let folded = Self::fold_adjacent_bits(n as u32);
        Self::is_all_ones(folded)
    }
}

#[cfg(test)]
mod tests {
    use super::Solution;

    #[test]
    fn alternating_bits_true_cases() {
        assert!(Solution::has_alternating_bits(1)); // 1
        assert!(Solution::has_alternating_bits(5)); // 101
        assert!(Solution::has_alternating_bits(10)); // 1010
    }

    #[test]
    fn alternating_bits_false_cases() {
        assert!(!Solution::has_alternating_bits(3)); // 11
        assert!(!Solution::has_alternating_bits(7)); // 111
        assert!(!Solution::has_alternating_bits(11)); // 1011
    }
}
