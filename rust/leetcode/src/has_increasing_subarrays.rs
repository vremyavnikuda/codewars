#!/usr/bin/env rust-script

pub struct Solution;
impl Solution {
    pub fn has_increasing_subarrays(nums: Vec<i32>, k: i32) -> bool {
        if k == 0 {
            return true;
        }
        let mut max_valid_length = 0;
        let mut previous_length = 0;
        let mut current_length = 0;
        let n = nums.len();
        for i in 0..n {
            current_length += 1;
            if i == n - 1 || nums[i] >= nums[i + 1] {
                max_valid_length = std::cmp::max(
                    max_valid_length,
                    std::cmp::max(
                        current_length / 2,
                        std::cmp::min(previous_length, current_length),
                    ),
                );
                previous_length = current_length;
                current_length = 0;
            }
        }
        max_valid_length >= k as usize
    }
}

fn main() {
    let nums1 = vec![2, 5, 7, 8, 9, 2, 3, 4, 3, 1];
    let k1 = 3;
    println!("Input: nums = {:?}, k = {}", nums1, k1);
    println!("Result: {}", Solution::has_increasing_subarrays(nums1, k1));

    let nums2 = vec![1, 2, 3, 4, 4, 4, 4, 5, 6, 7];
    let k2 = 2;
    println!("\nInput: nums = {:?}, k = {}", nums2, k2);
    println!("Result: {}", Solution::has_increasing_subarrays(nums2, k2));
}
