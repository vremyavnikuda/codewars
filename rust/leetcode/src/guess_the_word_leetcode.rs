#!/usr/bin/env rust-script

use std::cell::Cell;

pub struct Master {
    secret: String,
    guesses: Cell<usize>,
}

impl Master {
    pub fn new(secret: String) -> Self {
        Master {
            secret,
            guesses: Cell::new(0),
        }
    }

    pub fn guess(&self, word: String) -> i32 {
        self.guesses.set(self.guesses.get() + 1);
        if word.len() != 6 {
            return -1;
        }

        let mut matches = 0;
        let secret_bytes = self.secret.as_bytes();
        let word_bytes = word.as_bytes();

        for i in 0..6 {
            if secret_bytes[i] == word_bytes[i] {
                matches += 1;
            }
        }

        matches
    }

    pub fn get_guesses(&self) -> usize {
        self.guesses.get()
    }
}

pub struct Solution;

impl Solution {
    pub fn find_secret_word(words: Vec<String>, master: &Master) {
        let mut possible = words;

        for _ in 0..30 {
            if possible.is_empty() {
                break;
            }

            let current = Self::pick_word(&possible);
            let result = master.guess(current.clone());

            if result == 6 {
                return;
            }

            possible.retain(|word| Self::count_matches(&current, word) == result);
        }
    }

    fn count_matches(w1: &str, w2: &str) -> i32 {
        let b1 = w1.as_bytes();
        let b2 = w2.as_bytes();
        let mut matches = 0;

        for i in 0..6 {
            if b1[i] == b2[i] {
                matches += 1;
            }
        }

        matches
    }

    fn pick_word(words: &[String]) -> String {
        if words.len() == 1 {
            return words[0].clone();
        }

        if words.len() <= 2 {
            return words[0].clone();
        }

        let mut best = words[0].clone();
        let mut best_score = usize::MAX;

        for candidate in words {
            let mut buckets = [0; 7];
            
            for other in words {
                if candidate != other {
                    let matches = Self::count_matches(candidate, other) as usize;
                    buckets[matches] += 1;
                }
            }

            let score: usize = buckets.iter().map(|&x| x * x).sum();

            if score < best_score {
                best_score = score;
                best = candidate.clone();
            }
        }

        best
    }
}
#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_example_1() {
        let secret = "acckzz".to_string();
        let words = vec![
            "acckzz".to_string(),
            "ccbazz".to_string(),
            "eiowzz".to_string(),
            "abcczz".to_string(),
        ];
        let master = Master::new(secret);

        Solution::find_secret_word(words, &master);

        assert!(master.get_guesses() <= 30);
    }

    #[test]
    fn test_example_2() {
        let secret = "hamada".to_string();
        let words = vec!["hamada".to_string(), "khaled".to_string()];
        let master = Master::new(secret);

        Solution::find_secret_word(words, &master);

        assert!(master.get_guesses() <= 30);
    }

    #[test]
    fn test_count_matches() {
        assert_eq!(Solution::count_matches("acckzz", "acckzz"), 6);
        assert_eq!(Solution::count_matches("acckzz", "ccbazz"), 3);
        assert_eq!(Solution::count_matches("acckzz", "eiowzz"), 2);
        assert_eq!(Solution::count_matches("acckzz", "abcczz"), 4);
    }
}

fn main() {
    let secret = "acckzz".to_string();
    let words = vec![
        "acckzz".to_string(),
        "ccbazz".to_string(),
        "eiowzz".to_string(),
        "abcczz".to_string(),
    ];
    let master = Master::new(secret.clone());

    println!("Secret word: {}", secret);
    println!("Word list: {:?}", words);
    
    Solution::find_secret_word(words, &master);
    
    println!("Total guesses: {}", master.get_guesses());
}
