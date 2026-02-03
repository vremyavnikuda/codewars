#!/usr/bin/env rust-script

pub struct Solution;

impl Solution {
    pub fn final_value_after_operations(operations: Vec<String>) -> i32 {
        let mut x = 0;

        for op in operations {
            if op.chars().nth(1).unwrap() == '+' {
                x += 1;
            } else {
                x -= 1;
            }
        }

        x
    }
}

fn main() {
    let ops1 = vec!["--X".to_string(), "X++".to_string(), "X++".to_string()];
    println!("Input: {:?}", ops1);
    println!("Result: {}", Solution::final_value_after_operations(ops1));

    let ops2 = vec!["++X".to_string(), "++X".to_string(), "X++".to_string()];
    println!("\nInput: {:?}", ops2);
    println!("Result: {}", Solution::final_value_after_operations(ops2));
}
