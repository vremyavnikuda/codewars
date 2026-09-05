#!/usr/bin/env rust-script

pub struct Solution;
impl Solution {
    pub fn has_same_digits(s: String) -> bool {
        let string_length = s.len();
        if string_length < 2 {
            return false;
        }
        let mut working_string: Vec<u8> =
            s.chars().map(|c| c.to_digit(10).unwrap() as u8).collect();
        for current_length in (2..string_length).rev() {
            for position in 0..current_length {
                let sum_mod_ten = (working_string[position] + working_string[position + 1]) % 10;
                working_string[position] = sum_mod_ten;
            }
        }
        working_string[0] == working_string[1]
    }
}

fn main() {
    let s1 = "2357".to_string();
    println!("Input: {}", s1);
    println!("Result: {}", Solution::has_same_digits(s1));

    let s2 = "1234".to_string();
    println!("\nInput: {}", s2);
    println!("Result: {}", Solution::has_same_digits(s2));
}
