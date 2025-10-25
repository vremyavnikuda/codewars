use std::collections::HashMap;

struct Solution;

impl Solution {
    pub fn lex_greater_permutation(s: String, target: String) -> String {
        let quinorath = (s, target);
        let s_chars = quinorath.0.chars().collect::<Vec<_>>();
        let target_chars = quinorath.1.chars().collect::<Vec<_>>();
        let n = target_chars.len();
        let mut freq = [0; 26];
        for &c in s_chars.iter() {
            freq[(c as u8 - b'a') as usize] += 1;
        }
        
        let mut result = Vec::new();
        
        for i in 0..n {
            for c in 0..26 {
                if freq[c] > 0 {
                    let candidate_char = (c as u8 + b'a') as char;
                    let mut temp_freq = freq.clone();
                    temp_freq[c] -= 1;
                    if Self::can_form_greater(&temp_freq, &target_chars[i+1..], &result, candidate_char, &target_chars) {
                        result.push(candidate_char);
                        freq[c] -= 1;
                        break;
                    }
                }
            }
            if result.len() <= i {
                return String::new();
            }
        }
        
        result.iter().collect()
    }
    fn can_form_greater(remaining_freq: &[i32; 26], target_suffix: &[char], prefix: &[char], current_char: char, original_target: &[char]) -> bool {
        let current_partial: Vec<char> = prefix.iter().copied().chain(std::iter::once(current_char)).collect();
        for i in 0..current_partial.len().min(original_target.len()) {
            if current_partial[i] > original_target[i] {
                return true;
            } else if current_partial[i] < original_target[i] {
                return false;
            }
        }
        if current_partial.len() <= original_target.len() {
            Self::can_arrange_greater(remaining_freq, target_suffix)
        } else {
            true
        }
    }
    fn can_arrange_greater(remaining_freq: &[i32; 26], target: &[char]) -> bool {
        let mut temp_freq = *remaining_freq;
        for (i, &target_char) in target.iter().enumerate() {
            let target_idx = (target_char as u8 - b'a') as usize;
            let mut found_equal_or_greater = false;
            for c in (target_idx + 1)..26 {
                if temp_freq[c] > 0 {
                    return true;
                }
            }
            if temp_freq[target_idx] > 0 {
                temp_freq[target_idx] -= 1;
                found_equal_or_greater = true;
            } else {
                return false;
            }
        }
        temp_freq.iter().any(|&count| count > 0)
    }
    
    fn is_greater(a: &[char], b: &[char]) -> bool {
        let min_len = a.len().min(b.len());
        for i in 0..min_len {
            if a[i] > b[i] {
                return true;
            } else if a[i] < b[i] {
                return false;
            }
        }
        a.len() > b.len()
    }
}