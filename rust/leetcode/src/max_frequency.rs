#!/usr/bin/env rust-script

pub struct Solution;
impl Solution {
    pub fn max_frequency(nums: Vec<i32>, k: i32, num_operations: i32) -> i32 {
        use std::collections::{BTreeMap, HashMap};

        let mut frequency_map: HashMap<i32, i32> = HashMap::new();

        let mut range_difference: BTreeMap<i32, i32> = BTreeMap::new();

        for &num in &nums {
            *frequency_map.entry(num).or_insert(0) += 1;
            range_difference.entry(num).or_insert(0);
            *range_difference.entry(num - k).or_insert(0) += 1;
            *range_difference.entry(num + k + 1).or_insert(0) -= 1;
        }
        let mut max_result = 0;
        let mut current_range_count = 0;
        for (&position, &difference) in &range_difference {
            current_range_count += difference;
            let existing_count = *frequency_map.get(&position).unwrap_or(&0);
            max_result = max_result.max(current_range_count.min(existing_count + num_operations));
        }
        max_result
    }
}


fn main() {
    let nums1 = vec![1, 4, 5];
    let k1 = 1;
    let num_operations1 = 2;
    println!("Input: nums = {:?}, k = {}, numOperations = {}", nums1, k1, num_operations1);
    println!("Result: {}", Solution::max_frequency(nums1, k1, num_operations1));
    
    let nums2 = vec![5, 11, 20, 20];
    let k2 = 5;
    let num_operations2 = 1;
    println!("\nInput: nums = {:?}, k = {}, numOperations = {}", nums2, k2, num_operations2);
    println!("Result: {}", Solution::max_frequency(nums2, k2, num_operations2));
}
