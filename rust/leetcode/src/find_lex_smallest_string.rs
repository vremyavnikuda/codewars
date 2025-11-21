#!/usr/bin/env rust-script

use std::collections::HashSet;

use std::collections::VecDeque;

pub struct Solution;

impl Solution {
    pub fn find_lex_smallest_string(s: String, a: i32, b: i32) -> String {
        let mut visited = HashSet::new();
        let mut queue = VecDeque::new();

        queue.push_back(s.clone());
        visited.insert(s.clone());

        let mut result = s;

        while !queue.is_empty() {
            let current = queue.pop_front().unwrap();

            if current < result {
                result = current.clone();
            }

            let mut next1 = String::with_capacity(current.len());
            for (i, c) in current.chars().enumerate() {
                if i % 2 == 1 {
                    // odd index
                    let digit = c.to_digit(10).unwrap();
                    let new_digit = (digit + (a as u32)) % 10;
                    next1.push_str(&new_digit.to_string());
                } else {
                    next1.push(c);
                }
            }

            if !visited.contains(&next1) {
                visited.insert(next1.clone());
                queue.push_back(next1);
            }

            let len = current.len();
            let rotate_pos = (b as usize) % len;
            let next2 = current[rotate_pos..].to_string() + &current[..rotate_pos];

            if !visited.contains(&next2) {
                visited.insert(next2.clone());
                queue.push_back(next2);
            }
        }

        result
    }
}

fn main() {
    let s = "5525".to_string();
    let a = 9;
    let b = 2;
    let result = Solution::find_lex_smallest_string(s.clone(), a, b);
    println!("Input: s = {}, a = {}, b = {}", s, a, b);
    println!("Result: {}", result);
    
    let s2 = "74".to_string();
    let a2 = 5;
    let b2 = 1;
    let result2 = Solution::find_lex_smallest_string(s2.clone(), a2, b2);
    println!("\nInput: s = {}, a = {}, b = {}", s2, a2, b2);
    println!("Result: {}", result2);
}
