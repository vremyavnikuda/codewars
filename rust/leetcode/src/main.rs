mod adjacent_increasing_subarrays;
mod count_valid_selections;
mod find_itinerary;
mod find_lex_smallest_string;
mod guess_the_word;
mod has_increasing_subarrays;
mod has_increasing_subarrays;
mod has_increasing_subarrays;
mod has_same_digits;
mod int_to_roman;
mod kth_largest_element;
mod letter_combinations;
mod longest_balanced_abc;
mod longest_balanced_substring;
mod max_frequency;
mod max_frequency_2;
mod max_partitions_after_operations;
mod merge;
mod merge_k_lists;
mod missing_multiple;
mod next_beautiful_number;
mod num_water_bottles;
mod number_of_beams;
mod regex_matching;
mod remove_duplicates;
mod remove_element;
mod roman_to_int;
mod shortest_palindrome;
mod simple_bank_system;
mod smallest_missing_integer;
mod smallest_number;
mod sum_ancestors_perfect_square;
mod sum_divisible_by_k;
mod sum_frequency_divisible;
mod total_money;
mod type_of_triangle;
struct Solution;

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
    let test1 = "babad".to_string();
    let result1 = Solution::longest_palindrome(test1);
    println!("Test 1: {}", result1);

    let test2 = "cbbd".to_string();
    let result2 = Solution::longest_palindrome(test2);
    println!("Test 2: {}", result2);

    let test3 = "aacecaaa".to_string();
    let result3 = shortest_palindrome::Solution::shortest_palindrome(test3);
    println!("Test 1: {}", result3);

    let test4 = "abcd".to_string();
    let result4 = shortest_palindrome::Solution::shortest_palindrome(test4);
    println!("Test 2: {}", result4);

    let test5 = vec![3, 2, 1, 5, 6, 4];
    let result5 = kth_largest_element::Solution::find_kth_largest(test5, 2);
    println!("Test 1: {}", result5);

    let test6 = vec![3, 2, 3, 1, 2, 4, 5, 5, 6];
    let result6 = kth_largest_element::Solution::find_kth_largest(test6, 4);
    println!("Test 2: {}", result6);

    let test7 = vec![2, 5, 7, 8, 9, 2, 3, 4, 3, 1];
    let result7 = adjacent_increasing_subarrays::Solution::max_increasing_subarrays(test7);
    println!("Test 1: {}", result7);

    let test8 = vec![1, 2, 3, 4, 4, 4, 4, 5, 6, 7];
    let result8 = adjacent_increasing_subarrays::Solution::max_increasing_subarrays(test8);
    println!("Test 2: {}", result8);

    let test9 = vec![3, 3, 3];
    let result9 = type_of_triangle::Solution::triangle_type(test9);
    println!("Test 1: {}", result9);

    let test10 = vec![3, 4, 5];
    let result10 = type_of_triangle::Solution::triangle_type(test10);
    println!("Test 2: {}", result10);

    let test13 = "abbac".to_string();
    let result13 = longest_balanced_substring::Solution::longest_balanced(test13);
    println!("Test 1: {}", result13);

    let test14 = "zzabccy".to_string();
    let result14 = longest_balanced_substring::Solution::longest_balanced(test14);
    println!("Test 2: {}", result14);

    let test15 = "abbac".to_string();
    let result15 = longest_balanced_abc::Solution::longest_balanced(test15);
    println!("Test 1: {}", result15);

    let test16 = "aabcc".to_string();
    let result16 = longest_balanced_abc::Solution::longest_balanced(test16);
    println!("Test 2: {}", result16);

    let test17 = sum_ancestors_perfect_square::Solution::sum_of_ancestors(
        3,
        vec![vec![0, 1], vec![1, 2]],
        vec![2, 8, 2]
    );
    println!("Test 1: {} (expected: 3)", test17);

    let test18 = sum_ancestors_perfect_square::Solution::sum_of_ancestors(
        3,
        vec![vec![0, 1], vec![0, 2]],
        vec![1, 2, 4]
    );
    println!("Test 2: {} (expected: 1)", test18);

    // Large test
    let n = 100000i64;
    let mut edges = Vec::new();
    for i in 0..n - 1 {
        edges.push(vec![i as i32, (i + 1) as i32]);
    }

    let mut nums = Vec::new();
    for i in 0..n {
        let val = (2 * (i + 1) * (i + 1)) as i32;
        nums.push(val);
    }

    println!("First few signatures:");
    for i in 0..5 {
        let sig = sum_ancestors_perfect_square::Solution::get_signature(nums[i as usize]);
        println!("  nums[{}] = {} -> sig = {}", i, nums[i as usize], sig);
    }

    use std::time::Instant;
    let start = Instant::now();
    let result = sum_ancestors_perfect_square::Solution::sum_of_ancestors(n as i32, edges, nums);
    let duration = start.elapsed();

    let expected: i64 = ((n - 1) * n) / 2;
    println!("Result: {}", result);
    println!("Expected: {}", expected);
    println!("Match: {}", if result == expected { "YES" } else { "NO" });
    println!("Time: {:?}", duration);
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_example_1() {
        let result = Solution::longest_palindrome("babad".to_string());
        assert!(result == "bab" || result == "aba");
    }

    #[test]
    fn test_example_2() {
        assert_eq!(Solution::longest_palindrome("cbbd".to_string()), "bb");
    }

    #[test]
    fn test_single_char() {
        assert_eq!(Solution::longest_palindrome("a".to_string()), "a");
    }

    #[test]
    fn test_all_same() {
        assert_eq!(Solution::longest_palindrome("aaaa".to_string()), "aaaa");
    }

    #[test]
    fn test_no_palindrome() {
        assert_eq!(Solution::longest_palindrome("abc".to_string()), "a");
    }
}
