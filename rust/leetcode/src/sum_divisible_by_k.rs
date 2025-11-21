#!/usr/bin/env rust-script

use std::collections::HashMap;
pub struct Solution;
impl Solution {
    pub fn sum_divisible_by_k(nums: Vec<i32>, k: i32) -> i32 {
        let mut freq_map: HashMap<i32, i32> = HashMap::new();
        for &num in &nums {
            *freq_map.entry(num).or_insert(0) += 1;
        }

        let mut sum = 0;
        for (&num, &count) in &freq_map {
            if count % k == 0 {
                sum += num * count;
            }
        }

        sum
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
