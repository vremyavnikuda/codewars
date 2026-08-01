pub mod adjacent_increasing_subarrays;
pub mod convert;
pub mod count_palindromic_subsequence;
pub mod count_unguarded;
pub mod count_valid_selections;
pub mod final_value_after_operations;
pub mod find_itinerary;
pub mod find_lex_smallest_string;
pub mod guess_the_word;
pub mod guess_the_word_leetcode;
pub mod has_increasing_subarrays;
pub mod has_same_digits;
pub mod int_to_roman;
pub mod k_length_apart;
pub mod kth_largest_element;
pub mod letter_combinations;
pub mod lex_greater_permutation;
pub mod longest_balanced;
pub mod longest_balanced_abc;
pub mod longest_balanced_q4;
pub mod longest_balanced_substring;
pub mod longest_palindrome;
pub mod max_frequency;
pub mod max_frequency_2;
pub mod max_partitions_after_operations;
pub mod merge;
pub mod merge_k_lists;
pub mod min_cost;
pub mod min_number_operations;
pub mod missing_multiple;
pub mod modified_list;
pub mod next_beautiful_number;
pub mod num_water_bottles;
pub mod number_of_beams;
pub mod number_of_substrings;
pub mod process_queries;
#[path = "q2/q2_predict_the_winner.rs"]
pub mod q2_predict_the_winner;
#[path = "q2/q2_robotSim.rs"]
pub mod q2_robotSim;
#[path = "q2/q2_sum_and_multiply.rs"]
pub mod q2_sum_and_multiply;
#[path = "q2/q2_unique_xor_triplets.rs"]
pub mod q2_unique_xor_triplets;
#[path = "q3/q3_max_active_sections_after_trade.rs"]
pub mod q3_max_active_sections_after_trade;
pub mod range_add_queries;
pub mod regex_matching;
pub mod regex_matching_leetcode;
pub mod remove_duplicates;
pub mod remove_element;
pub mod roman_to_int;
pub mod shortest_palindrome;
pub mod simple_bank_system;
pub mod smallest_missing_integer;
pub mod smallest_number;
pub mod sum_ancestors_perfect_square;
pub mod sum_divisible_by_k;
pub mod sum_frequency_divisible;
pub mod test_balanced;
pub mod test_final_value;
pub mod test_longest_balanced_q4;
pub mod total_money;
pub mod type_of_triangle;

#[cfg(test)]
mod tests {
    use crate::remove_element::Solution;

    #[test]
    fn test_remove_element() {
        // Test case 1: nums = [3,2,2,3], val = 3
        let mut nums1 = vec![3, 2, 2, 3];
        let k1 = Solution::remove_element(&mut nums1, 3);
        assert_eq!(k1, 2);
        assert_eq!(&nums1[..k1 as usize], &[2, 2]);

        // Test case 2: nums = [0,1,2,2,3,0,4,2], val = 2
        let mut nums2 = vec![0, 1, 2, 2, 3, 0, 4, 2];
        let k2 = Solution::remove_element(&mut nums2, 2);
        assert_eq!(k2, 5);
        // The first k elements can be in any order, so we sort for comparison
        let mut result2 = nums2[..k2 as usize].to_vec();
        result2.sort();
        assert_eq!(result2, vec![0, 0, 1, 3, 4]);
    }
}

// Add tests for longest_balanced_q4
#[cfg(test)]
mod longest_balanced_tests {
    use crate::longest_balanced_q4::Solution;

    #[test]
    fn test_longest_balanced_examples() {
        // Test Example 1
        let nums1 = vec![2, 5, 4, 3];
        let result1 = Solution::longest_balanced(nums1);
        assert_eq!(result1, 4);

        // Test Example 2
        let nums2 = vec![3, 2, 2, 5, 4];
        let result2 = Solution::longest_balanced(nums2);
        assert_eq!(result2, 5);

        // Test Example 3
        let nums3 = vec![1, 2, 3, 2];
        let result3 = Solution::longest_balanced(nums3);
        assert_eq!(result3, 3);
    }
}

#[cfg(test)]
mod q3_max_active_sections_tests {
    use crate::q3_max_active_sections_after_trade::Solution;

    #[test]
    fn test_example_1() {
        let s = "01".to_string();
        let queries = vec![vec![0, 1]];
        let result = Solution::max_active_sections_after_trade(s, queries);
        assert_eq!(result, vec![1]);
    }

    #[test]
    fn test_example_2() {
        let s = "0100".to_string();
        let queries = vec![vec![0, 3], vec![1, 3], vec![2, 3]];
        let result = Solution::max_active_sections_after_trade(s, queries);
        assert_eq!(result, vec![4, 1, 1]);
    }

    #[test]
    fn test_all_ones() {
        let s = "1111".to_string();
        let queries = vec![vec![0, 3]];
        let result = Solution::max_active_sections_after_trade(s, queries);
        assert_eq!(result, vec![4]);
    }

    #[test]
    fn test_no_ones() {
        let s = "0000".to_string();
        let queries = vec![vec![0, 3]];
        let result = Solution::max_active_sections_after_trade(s, queries);
        assert_eq!(result, vec![0]);
    }

    #[test]
    fn test_single_group() {
        let s = "1001".to_string();
        let queries = vec![vec![0, 3], vec![1, 2]];
        let result = Solution::max_active_sections_after_trade(s, queries);
        assert_eq!(result, vec![2, 2]);
    }

    #[test]
    fn test_multiple_queries() {
        let s = "01010".to_string();
        let queries = vec![vec![0, 4], vec![1, 3], vec![0, 2]];
        let result = Solution::max_active_sections_after_trade(s, queries);
        assert_eq!(result, vec![4, 2, 4]);
    }
}
