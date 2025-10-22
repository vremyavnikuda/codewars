use std::collections::HashMap;

impl Solution {
    pub fn roman_to_int(s: String) -> i32 {
        let roman_values: HashMap<char, i32> = [
            ('I', 1),
            ('V', 5),
            ('X', 10),
            ('L', 50),
            ('C', 100),
            ('D', 500),
            ('M', 1000)
        ].iter().cloned().collect();
        let chars: Vec<char> = s.chars().collect();
        if chars.is_empty() {
            return 0;
        }
        let mut result = roman_values[&chars[chars.len() - 1]];
        for i in 0..chars.len() - 1 {
            let sign = if roman_values[&chars[i]] < roman_values[&chars[i + 1]] { -1 } else { 1 };
            result += sign * roman_values[&chars[i]];
        }
        result
    }
}