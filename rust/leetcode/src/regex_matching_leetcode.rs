#!/usr/bin/env rust-script

pub struct Solution;

impl Solution {
    pub fn is_match(s: String, p: String) -> bool {
        let s = s.as_bytes();
        let p = p.as_bytes();
        let m = s.len();
        let n = p.len();
        let mut dp = vec![vec![false; n + 1]; m + 1];
        dp[0][0] = true;
        for j in 2..=n {
            if p[j - 1] == b'*' {
                dp[0][j] = dp[0][j - 2];
            }
        }
        
        for i in 1..=m {
            for j in 1..=n {
                if p[j - 1] == b'*' {
                    dp[i][j] = dp[i][j - 2];
                    let prev_char = p[j - 2];
                    if prev_char == b'.' || prev_char == s[i - 1] {
                        dp[i][j] = dp[i][j] || dp[i - 1][j];
                    }
                } else if p[j - 1] == b'.' || p[j - 1] == s[i - 1] {
                    dp[i][j] = dp[i - 1][j - 1];
                }
            }
        }
        
        dp[m][n]
    }
}


fn main() {
    let s1 = "aa".to_string();
    let p1 = "a".to_string();
    println!("Input: s = {}, p = {}", s1, p1);
    println!("Result: {}", Solution::is_match(s1, p1));
    
    let s2 = "aa".to_string();
    let p2 = "a*".to_string();
    println!("\nInput: s = {}, p = {}", s2, p2);
    println!("Result: {}", Solution::is_match(s2, p2));
}
