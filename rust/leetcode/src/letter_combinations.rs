impl Solution {
    pub fn letter_combinations(digits: String) -> Vec<String> {
        if digits.is_empty() {
            return vec![];
        }
        let digit_to_letters = [
            "abc",  // 2
            "def",  // 3
            "ghi",  // 4
            "jkl",  // 5
            "mno",  // 6
            "pqrs", // 7
            "tuv",  // 8
            "wxyz", // 9
        ];
        let mut result = vec!["".to_string()];
        for digit in digits.chars() {
            let letters = digit_to_letters[(digit as u8 - b'2') as usize];
            let mut new_combinations = Vec::new();
            for existing_combination in &result {
                for letter in letters.chars() {
                    new_combinations.push(format!("{}{}", existing_combination, letter));
                }
            }
            result = new_combinations;
        }
        result
    }
}
