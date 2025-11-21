#!/usr/bin/env rust-script

pub struct Solution;
impl Solution {
    pub fn min_number_operations(target: Vec<i32>) -> i32 {
        if target.is_empty() {
            return 0;
        }
        let mut t1 = target[0];
        for na1 in 1..target.len() {
            if target[na1] > target[na1 - 1] {
                t1 += target[na1] - target[na1 - 1];
            }
        }
        t1
    }
}


fn main() {
    let target1 = vec![1, 2, 3, 2, 1];
    println!("Input: {:?}", target1);
    println!("Result: {}", Solution::min_number_operations(target1));
    
    let target2 = vec![3, 1, 1, 2];
    println!("\nInput: {:?}", target2);
    println!("Result: {}", Solution::min_number_operations(target2));
}
