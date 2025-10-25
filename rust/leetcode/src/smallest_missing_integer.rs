use std::collections::HashMap;

pub struct Solution;

impl Solution {
    pub fn find_smallest_integer(nums: Vec<i32>, value: i32) -> i32 {
        let mut freq: HashMap<i32, i32> = HashMap::new();

        for &num in &nums {
            let remainder = num.rem_euclid(value);
            *freq.entry(remainder).or_insert(0) += 1;
        }

        let mut mex = 0;
        loop {
            let remainder = mex % value;
            if let Some(count) = freq.get_mut(&remainder) {
                if *count > 0 {
                    *count -= 1;
                    mex += 1;
                } else {
                    break;
                }
            } else {
                break;
            }
        }

        mex
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_example_1() {
        let nums = vec![1, -10, 7, 13, 6, 8];
        let value = 5;
        assert_eq!(Solution::find_smallest_integer(nums, value), 4);
    }

    #[test]
    fn test_example_2() {
        let nums = vec![1, -10, 7, 13, 6, 8];
        let value = 7;
        assert_eq!(Solution::find_smallest_integer(nums, value), 2);
    }

    #[test]
    fn test_single_element() {
        let nums = vec![3];
        let value = 5;
        assert_eq!(Solution::find_smallest_integer(nums, value), 0);
    }

    #[test]
    fn test_all_same_remainder() {
        let nums = vec![0, 5, 10, 15];
        let value = 5;
        assert_eq!(Solution::find_smallest_integer(nums, value), 1);
    }
}
