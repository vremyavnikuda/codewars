#!/usr/bin/env rust-script

use std::collections::HashMap;

pub struct Solution;

impl Solution {
    pub fn sum_divisible_by_k(nums: Vec<i32>, k: i32) -> i64 {
        let mut freq_map: HashMap<i32, i32> = HashMap::new();

        for &num in &nums {
            *freq_map.entry(num).or_insert(0) += 1;
        }

        let mut sum: i64 = 0;

        for (&num, &count) in &freq_map {
            if count % k == 0 {
                sum += (num as i64) * (count as i64);
            }
        }

        sum
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_example_from_problem() {
        assert_eq!(
            Solution::sum_divisible_by_k(vec![1, 2, 2, 3, 3, 3, 3, 4], 2),
            16
        );
    }

    #[test]
    fn test_example_2_from_problem() {
        assert_eq!(Solution::sum_divisible_by_k(vec![1, 2, 3, 4, 5], 2), 0);
    }

    #[test]
    fn test_example_3_from_problem() {
        assert_eq!(Solution::sum_divisible_by_k(vec![4, 4, 4, 1, 2, 3], 3), 12);
    }

    #[test]
    fn test_basic_case() {
        assert_eq!(Solution::sum_divisible_by_k(vec![1, 2, 3, 1, 2, 1], 3), 3);
    }

    #[test]
    fn test_all_same_element() {
        assert_eq!(Solution::sum_divisible_by_k(vec![5, 5, 5, 5], 2), 20);
    }

    #[test]
    fn test_no_valid_frequency() {
        assert_eq!(Solution::sum_divisible_by_k(vec![1, 2, 3, 4], 2), 0);
    }

    #[test]
    fn test_k_equals_1() {
        assert_eq!(Solution::sum_divisible_by_k(vec![1, 2, 3, 4, 5], 1), 15);
    }

    #[test]
    fn test_multiple_elements_divisible() {
        assert_eq!(
            Solution::sum_divisible_by_k(vec![2, 2, 3, 3, 3, 5, 5, 5], 2),
            4
        );
    }

    #[test]
    fn test_negative_numbers() {
        assert_eq!(
            Solution::sum_divisible_by_k(vec![-1, -1, -1, 2, 2, 2], 3),
            3
        );
    }

    #[test]
    fn test_single_element() {
        assert_eq!(Solution::sum_divisible_by_k(vec![10], 1), 10);
    }

    #[test]
    fn test_zeros() {
        assert_eq!(Solution::sum_divisible_by_k(vec![0, 0, 0, 0], 2), 0);
    }

    #[test]
    fn test_large_numbers() {
        assert_eq!(
            Solution::sum_divisible_by_k(vec![1000000, 1000000, 1000000, 1000000], 4),
            4000000
        );
    }

    #[test]
    fn test_mixed_frequencies() {
        assert_eq!(
            Solution::sum_divisible_by_k(vec![1, 1, 2, 2, 2, 2, 3, 3, 3, 4, 4, 4, 4, 4, 4], 2),
            34
        );
    }
}

fn main() {
    let nums1 = vec![1, 2, 3, 4, 5];
    let k1 = 3;
    println!("Input: nums = {:?}, k = {}", nums1, k1);
    println!("Result: {}", Solution::sum_divisible_by_k(nums1, k1));

    let nums2 = vec![5, 5, 5, 5];
    let k2 = 1;
    println!("\nInput: nums = {:?}, k = {}", nums2, k2);
    println!("Result: {}", Solution::sum_divisible_by_k(nums2, k2));
}
