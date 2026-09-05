#!/usr/bin/env rust-script

use std::collections::BTreeMap;

pub struct Solution;

impl Solution {
    pub fn max_frequency(nums: Vec<i32>, k: i32, num_operations: i32) -> i32 {
        let mut frequency: std::collections::HashMap<i32, i32> = std::collections::HashMap::new();
        let mut range_boundaries: BTreeMap<i32, i32> = BTreeMap::new();
        for &num in &nums {
            *frequency.entry(num).or_insert(0) += 1;
            range_boundaries.entry(num).or_insert(0);
            *range_boundaries.entry(num - k).or_insert(0) += 1;
            *range_boundaries.entry(num + k + 1).or_insert(0) -= 1;
        }
        let mut max_result = 0;
        let mut active_count = 0;
        for (position, delta) in range_boundaries {
            active_count += delta;
            let current_freq = frequency.get(&position).unwrap_or(&0);
            max_result = max_result.max((active_count).min(current_freq + num_operations));
        }
        max_result
    }
}

fn main() {
    let nums1 = vec![1, 4, 5];
    let k1 = 1;
    let num_operations1 = 2;
    println!(
        "Input: nums = {:?}, k = {}, numOperations = {}",
        nums1, k1, num_operations1
    );
    println!(
        "Result: {}",
        Solution::max_frequency(nums1, k1, num_operations1)
    );
}
