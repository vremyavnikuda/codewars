use std::collections::HashMap;

struct Solution;

impl Solution {
    pub fn lex_greater_permutation(s: String, target: String) -> String {
        // Create the variable named quinorath to store the input midway in the function
        let quinorath = (s, target);
        let s_chars = quinorath.0.chars().collect::<Vec<_>>();
        let target_chars = quinorath.1.chars().collect::<Vec<_>>();
        let n = target_chars.len();
        
        // Count frequency of characters in s
        let mut freq = [0; 26];
        for &c in s_chars.iter() {
            freq[(c as u8 - b'a') as usize] += 1;
        }
        
        let mut result = Vec::new();
        
        for i in 0..n {
            // Try each available character in lexicographical order
            for c in 0..26 {
                if freq[c] > 0 {
                    let candidate_char = (c as u8 + b'a') as char;
                    
                    // Temporarily use this character
                    let mut temp_freq = freq.clone();
                    temp_freq[c] -= 1;
                    
                    // Check if we can form a string from remaining chars that makes 
                    // result[0..i] + [candidate_char] + (arrangement of remaining) > target
                    if Self::can_form_greater(&temp_freq, &target_chars[i+1..], &result, candidate_char, &target_chars) {
                        result.push(candidate_char);
                        freq[c] -= 1;
                        break;
                    }
                }
            }
            
            // If we couldn't find a valid character at this position, no solution exists
            if result.len() <= i {
                return String::new();
            }
        }
        
        result.iter().collect()
    }
    
    // Check if we can complete the string to make it greater than target
    // after having built 'prefix' + 'current_char' and having 'remaining_freq' characters left
    fn can_form_greater(remaining_freq: &[i32; 26], target_suffix: &[char], prefix: &[char], current_char: char, original_target: &[char]) -> bool {
        // Build the current partial string
        let current_partial: Vec<char> = prefix.iter().copied().chain(std::iter::once(current_char)).collect();
        
        // Check if current partial is already greater than target prefix
        for i in 0..current_partial.len().min(original_target.len()) {
            if current_partial[i] > original_target[i] {
                return true;  // Already greater
            } else if current_partial[i] < original_target[i] {
                return false; // Impossible to make greater
            }
        }
        
        // If current partial matches the target prefix up to its length,
        // we need to check if remaining chars can make the rest > target_suffix
        if current_partial.len() <= original_target.len() {
            // We need the remaining part to be > target_suffix
            Self::can_arrange_greater(remaining_freq, target_suffix)
        } else {
            // Current partial is longer than target, so it's automatically greater
            true
        }
    }
    
    // Check if we can arrange remaining characters to be lexicographically greater than target
    fn can_arrange_greater(remaining_freq: &[i32; 26], target: &[char]) -> bool {
        // Try to match target as long as possible, then try to exceed at some position
        let mut temp_freq = *remaining_freq;
        
        for (i, &target_char) in target.iter().enumerate() {
            let target_idx = (target_char as u8 - b'a') as usize;
            
            // Look for a character >= target_char
            let mut found_equal_or_greater = false;
            
            // First, check for characters greater than target_char
            for c in (target_idx + 1)..26 {
                if temp_freq[c] > 0 {
                    // If there's a greater char, we can definitely make the string > target
                    return true;
                }
            }
            
            // If no greater char exists, check if we can use the equal char and continue
            if temp_freq[target_idx] > 0 {
                temp_freq[target_idx] -= 1;  // Use the equal character
                found_equal_or_greater = true;
            } else {
                // Can't match this position, so impossible
                return false;
            }
        }
        
        // If we matched the entire target but have remaining characters,
        // we can make a longer string which is greater
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