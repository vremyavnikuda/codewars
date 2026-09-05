#!/usr/bin/env rust-script

use std::collections::HashSet;
pub struct Solution;

impl Solution {
    pub fn missing_multiple(nums: Vec<i32>, k: i32) -> i32 {
        let num_set: HashSet<i32> = nums.into_iter().collect();

        let mut mult = k;
        while num_set.contains(&mult) {
            mult += k;
        }
        mult
    }
}

fn main() {
    let nums1 = vec![2, 4, 6];
    let k1 = 2;
    println!("Input: nums = {:?}, k = {}", nums1, k1);
    println!("Result: {}", Solution::missing_multiple(nums1, k1));

    let nums2 = vec![1, 3, 5, 7];
    let k2 = 2;
    println!("\nInput: nums = {:?}, k = {}", nums2, k2);
    println!("Result: {}", Solution::missing_multiple(nums2, k2));
}
