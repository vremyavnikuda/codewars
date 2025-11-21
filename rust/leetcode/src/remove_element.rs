#!/usr/bin/env rust-script

pub struct Solution;

impl Solution {
    pub fn remove_element(nums: &mut Vec<i32>, val: i32) -> i32 {
        let mut left = 0;
        
        for right in 0..nums.len() {
            if nums[right] != val {
                nums[left] = nums[right];
                left += 1;
            }
        }
        left as i32
    }
}


fn main() {
    let mut test1 = vec![3, 2, 2, 3];
    let k1 = Solution::remove_element(&mut test1, 3);
    println!("Test 1: nums=[3,2,2,3], val=3");
    println!("k = {}, nums = {:?}\n", k1, &test1[..k1 as usize]);
    
    let mut test2 = vec![0, 1, 2, 2, 3, 0, 4, 2];
    let k2 = Solution::remove_element(&mut test2, 2);
    println!("Test 2: nums=[0,1,2,2,3,0,4,2], val=2");
    println!("k = {}, nums = {:?}", k2, &test2[..k2 as usize]);
}
