#!/usr/bin/env rust-script

pub struct Solution;

impl Solution {
    pub fn count_palindromic_subsequence(s: String) -> i32 {
        let s_bytes = s.as_bytes();
        let mut result = 0;

        for ch in b'a'..=b'z' {
            let first = s_bytes.iter().position(|&c| c == ch);
            let last = s_bytes.iter().rposition(|&c| c == ch);

            if let (Some(f), Some(l)) = (first, last) {
                if f < l {
                    let mut mask = 0u32;
                    for &c in &s_bytes[f + 1..l] {
                        mask |= 1 << (c - b'a');
                    }
                    result += mask.count_ones() as i32;
                }
            }
        }
        result
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_example_1() {
        let s = "aabca".to_string();
        assert_eq!(Solution::count_palindromic_subsequence(s), 3);
    }

    #[test]
    fn test_example_2() {
        let s = "adc".to_string();
        assert_eq!(Solution::count_palindromic_subsequence(s), 0);
    }

    #[test]
    fn test_example_3() {
        let s = "bbcbaba".to_string();
        assert_eq!(Solution::count_palindromic_subsequence(s), 4);
    }
}

fn main() {
    let s = "aabca".to_string();
    let result = Solution::count_palindromic_subsequence(s.clone());
    println!("Input: {}", s);
    println!("Result: {}", result);

    let s2 = "bbcbaba".to_string();
    let result2 = Solution::count_palindromic_subsequence(s2.clone());
    println!("\nInput: {}", s2);
    println!("Result: {}", result2);
}
