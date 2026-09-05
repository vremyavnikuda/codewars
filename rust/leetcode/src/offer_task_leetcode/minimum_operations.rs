#!/usr/bin/env rust-script

pub struct Solution;

impl Solution {
    pub fn minimum_operations(nums: Vec<i32>) -> i32 {
        let mut q = 0;
        for q1 in nums {
            let q2 = q1 % 3;
            if q2 != 0 {
                q += q2.min(3 - q2);
            }
        }
        q
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_example_1() {
        assert_eq!(Solution::minimum_operations(vec![1, 2, 3, 4]), 3);
    }

    #[test]
    fn test_example_2() {
        assert_eq!(Solution::minimum_operations(vec![3, 6, 9]), 0);
    }
}

fn main() {
    let nums1 = vec![1, 2, 3, 4];
    println!("Input: {:?}", nums1);
    println!("Result: {}", Solution::minimum_operations(nums1));

    let nums2 = vec![3, 6, 9];
    println!("\nInput: {:?}", nums2);
    println!("Result: {}", Solution::minimum_operations(nums2));
}
