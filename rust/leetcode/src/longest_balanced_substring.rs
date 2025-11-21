#!/usr/bin/env rust-script

use std::collections::HashMap;

pub struct Solution;

impl Solution {
    pub fn longest_balanced(s: String) -> i32 {
        let bytes = s.as_bytes();
        let n = bytes.len();
        let mut max_len = 0;
        
        for i in 0..n {
            let mut freq: HashMap<u8, usize> = HashMap::new();
            
            for j in i..n {
                *freq.entry(bytes[j]).or_insert(0) += 1;
                
                if Self::is_balanced(&freq) {
                    max_len = max_len.max(j - i + 1);
                }
            }
        }
        
        max_len as i32
    }
    
    #[inline]
    fn is_balanced(freq: &HashMap<u8, usize>) -> bool {
        if freq.is_empty() {
            return false;
        }
        
        let first_count = *freq.values().next().unwrap();
        freq.values().all(|&count| count == first_count)
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_example_1() {
        assert_eq!(Solution::longest_balanced("abbac".to_string()), 4);
    }

    #[test]
    fn test_example_2() {
        assert_eq!(Solution::longest_balanced("zzabccy".to_string()), 4);
    }

    #[test]
    fn test_example_3() {
        assert_eq!(Solution::longest_balanced("aba".to_string()), 2);
    }

    #[test]
    fn test_single_char() {
        assert_eq!(Solution::longest_balanced("a".to_string()), 1);
    }

    #[test]
    fn test_all_same() {
        assert_eq!(Solution::longest_balanced("aaaa".to_string()), 4);
    }

    #[test]
    fn test_two_chars_equal() {
        assert_eq!(Solution::longest_balanced("aabb".to_string()), 4);
    }

    #[test]
    fn test_two_chars_unequal() {
        assert_eq!(Solution::longest_balanced("aaab".to_string()), 3);
    }

    #[test]
    fn test_three_chars_balanced() {
        assert_eq!(Solution::longest_balanced("aabbcc".to_string()), 6);
    }

    #[test]
    fn test_no_balance() {
        assert_eq!(Solution::longest_balanced("abcdef".to_string()), 6);
    }

    #[test]
    fn test_complex() {
        assert_eq!(Solution::longest_balanced("aabbccdd".to_string()), 8);
    }

    #[test]
    fn test_interleaved() {
        assert_eq!(Solution::longest_balanced("ababab".to_string()), 6);
    }

    #[test]
    fn test_partial_balance() {
        assert_eq!(Solution::longest_balanced("aabbbcc".to_string()), 4);
    }
}


fn main() {
    let s1 = "cabbacc".to_string();
    println!("Input: {}", s1);
    println!("Result: {}", Solution::longest_balanced(s1));
    
    let s2 = "aabbbcc".to_string();
    println!("\nInput: {}", s2);
    println!("Result: {}", Solution::longest_balanced(s2));
}
