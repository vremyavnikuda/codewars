#!/usr/bin/env rust-script

use std::collections::HashSet;

pub struct Solution;

impl Solution {
    pub fn longest_balanced(nums: Vec<i32>) -> i32 {
        let n = nums.len();
        let mut max_length = 0;

        for i in 0..n {
            let mut even_set = HashSet::new();
            let mut odd_set = HashSet::new();

            for j in i..n {
                if nums[j] % 2 == 0 {
                    even_set.insert(nums[j]);
                } else {
                    odd_set.insert(nums[j]);
                }

                if even_set.len() == odd_set.len() {
                    max_length = max_length.max((j - i + 1) as i32);
                }
            }
        }
        max_length
    }
}


fn main() {
    let nums1 = vec![2, 5, 4, 3];
    println!("Input: {:?}", nums1);
    println!("Result: {}", Solution::longest_balanced(nums1));
    
    let nums2 = vec![3, 2, 2, 5, 4];
    println!("\nInput: {:?}", nums2);
    println!("Result: {}", Solution::longest_balanced(nums2));
}
