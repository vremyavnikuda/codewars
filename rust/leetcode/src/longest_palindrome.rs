#!/usr/bin/env rust-script

pub struct Solution;

impl Solution {
    pub fn longest_palindrome(s: String) -> String {
        if s.is_empty() {
            return String::new();
        }

        let bytes = s.as_bytes();
        let mut start = 0;
        let mut max_len = 1;

        fn expand_around_center(s: &[u8], left: i32, right: i32) -> usize {
            let mut l = left;
            let mut r = right;

            while l >= 0 && r < (s.len() as i32) && s[l as usize] == s[r as usize] {
                l -= 1;
                r += 1;
            }

            (r - l - 1) as usize
        }

        for i in 0..bytes.len() {
            let len1 = expand_around_center(bytes, i as i32, i as i32);
            let len2 = expand_around_center(bytes, i as i32, (i + 1) as i32);
            let len = len1.max(len2);

            if len > max_len {
                max_len = len;
                start = i - (len - 1) / 2;
            }
        }

        s[start..start + max_len].to_string()
    }
}


fn main() {
    let s1 = "babad".to_string();
    println!("Input: {}", s1);
    println!("Result: {}", Solution::longest_palindrome(s1));
    
    let s2 = "cbbd".to_string();
    println!("\nInput: {}", s2);
    println!("Result: {}", Solution::longest_palindrome(s2));
}
