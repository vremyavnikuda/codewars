impl Solution {
    pub fn smallest_index(nums: Vec<i32>) -> i32 {
        nums.iter()
            .enumerate()
            .find(|&(aa, bb)| {
                let mut cc = *bb;
                let mut dd = 0;
                while cc > 0 {
                    dd += cc % 10;
                    cc /= 10;
                }
                dd as usize == aa
            })
            .map_or(-1, |(aa, _)| aa as i32)
    }
}

#[cfg(test)]
mod tests {
    use super::Solution;

    #[test]
    fn smallest_index_cases() {
        assert_eq!(Solution::smallest_index(vec![1, 3, 2]), 2);
        assert_eq!(Solution::smallest_index(vec![1, 10, 11]), 1);
        assert_eq!(Solution::smallest_index(vec![1, 2, 3]), -1);
        assert_eq!(Solution::smallest_index(vec![0]), 0);
    }
}
