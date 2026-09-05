#!/usr/bin/env rust-script

pub struct Solution;
impl Solution {
    pub fn k_length_apart(nums: Vec<i32>, k: i32) -> bool {
        let mut prev_one: i32 = -(k + 1);
        for (idx, value) in nums.into_iter().enumerate() {
            if value == 1 {
                if idx as i32 - prev_one - 1 < k {
                    return false;
                }
                prev_one = idx as i32;
            }
        }
        true
    }
}

fn main() {
    println!("=== K Length Apart ===\n");

    let test1 = Solution::k_length_apart(vec![1, 0, 0, 0, 1, 0, 0, 1], 2);
    println!(
        "Test 1: [1,0,0,0,1,0,0,1], k=2 => {} (expected true)",
        test1
    );

    let test2 = Solution::k_length_apart(vec![1, 0, 0, 1, 0, 1], 2);
    println!("Test 2: [1,0,0,1,0,1], k=2 => {} (expected false)", test2);
}
