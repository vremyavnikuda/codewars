#!/usr/bin/env rust-script

pub struct Solution;
impl Solution {
    pub fn remove_duplicates(nums: &mut Vec<i32>) -> i32 {
        if nums.is_empty() {
            return 0;
        }

        let mut unique_index = 0;

        for i in 1..nums.len() {
            if nums[i] != nums[unique_index] {
                unique_index += 1;
                nums[unique_index] = nums[i];
            }
        }

        (unique_index + 1) as i32
    }
}


fn main() {
    let mut test1 = vec![1, 1, 2];
    let k1 = Solution::remove_duplicates(&mut test1);
    println!("Test 1: nums={:?}, k={}", &test1[..k1 as usize], k1);
    
    let mut test2 = vec![0, 0, 1, 1, 1, 2, 2, 3, 3, 4];
    let k2 = Solution::remove_duplicates(&mut test2);
    println!("Test 2: nums={:?}, k={}", &test2[..k2 as usize], k2);
}
