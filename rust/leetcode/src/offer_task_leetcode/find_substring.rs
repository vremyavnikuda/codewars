#!/usr/bin/env rust-script

use std::collections::HashMap;

pub struct Solution;

impl Solution {
    pub fn find_substring(s: String, words: Vec<String>) -> Vec<i32> {
        let mut q = HashMap::new();
        for q1 in &words {
            *q.entry(q1.as_str()).or_insert(0) += 1;
        }

        let mut q2 = Vec::new();
        let q3 = s.len();
        let q4 = words.len();
        let q5 = words[0].len();

        for q6 in 0..q5 {
            let mut q7 = q6;
            let mut q8 = q6;
            let mut q9 = HashMap::new();

            while q8 + q5 <= q3 {
                let q10 = &s[q8..q8 + q5];
                q8 += q5;

                if !q.contains_key(q10) {
                    q9.clear();
                    q7 = q8;
                    continue;
                }

                *q9.entry(q10).or_insert(0) += 1;

                while q9[q10] > q[q10] {
                    let q11 = &s[q7..q7 + q5];
                    *q9.get_mut(q11).unwrap() -= 1;
                    if q9[q11] == 0 {
                        q9.remove(q11);
                    }
                    q7 += q5;
                }

                if q8 - q7 == q4 * q5 {
                    q2.push(q7 as i32);
                }
            }
        }

        q2
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_example_1() {
        let s = "barfoothefoobarman".to_string();
        let words = vec!["foo".to_string(), "bar".to_string()];
        let mut result = Solution::find_substring(s, words);
        result.sort();
        assert_eq!(result, vec![0, 9]);
    }

    #[test]
    fn test_example_2() {
        let s = "wordgoodgoodgoodbestword".to_string();
        let words = vec![
            "word".to_string(),
            "good".to_string(),
            "best".to_string(),
            "word".to_string(),
        ];
        let result = Solution::find_substring(s, words);
        assert_eq!(result, vec![]);
    }

    #[test]
    fn test_example_3() {
        let s = "barfoofoobarthefoobarman".to_string();
        let words = vec!["bar".to_string(), "foo".to_string(), "the".to_string()];
        let mut result = Solution::find_substring(s, words);
        result.sort();
        assert_eq!(result, vec![6, 9, 12]);
    }
}

fn main() {
    let s1 = "barfoothefoobarman".to_string();
    let words1 = vec!["foo".to_string(), "bar".to_string()];
    println!("Input: s = {}, words = {:?}", s1, words1);
    println!("Result: {:?}", Solution::find_substring(s1, words1));

    let s2 = "wordgoodgoodgoodbestword".to_string();
    let words2 = vec![
        "word".to_string(),
        "good".to_string(),
        "best".to_string(),
        "word".to_string(),
    ];
    println!("\nInput: s = {}, words = {:?}", s2, words2);
    println!("Result: {:?}", Solution::find_substring(s2, words2));
}
