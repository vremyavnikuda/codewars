mod adjacent_increasing_subarrays;
mod count_unguarded;
mod count_valid_selections;
mod find_itinerary;
mod find_lex_smallest_string;
mod guess_the_word;
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
mod min_cost;
mod min_number_operations;
mod missing_multiple;
mod modified_list;
mod next_beautiful_number;
mod num_water_bottles;
mod number_of_beams;
mod process_queries;
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
mod range_add_queries;
mod number_of_substrings;
mod convert;
mod k_length_apart;
mod count_palindromic_subsequence;
mod longest_palindrome;
mod final_value_after_operations;

fn main(){
    // adjacent_increasing_subarrays
    println!("Test: {}", adjacent_increasing_subarrays::Solution::max_increasing_subarrays(vec![1, 2, 3, 4, 4, 4, 4, 5, 6, 7]));

    // convert
    println!("Test: {}", convert::Solution::convert("PAYPALISHIRING".to_string(), 3));

    // count_palindromic_subsequence
    println!("Test: {}", count_palindromic_subsequence::Solution::count_palindromic_subsequence("aabca".to_string()));

    // count_unguarded
    println!("Test: {}", count_unguarded::Solution::count_unguarded(2, 2, vec![vec![0, 0], vec![0, 1]], vec![vec![0, 0], vec![1, 1]]));

    // count_valid_selections
    println!("Test: {}", count_valid_selections::Solution::count_valid_selections(vec![1, 2, 3, 4, 5]));

    // final_value_after_operations
    println!("Test: {}", final_value_after_operations::Solution::final_value_after_operations(vec!["--X++".to_string(), "++X++".to_string()]));

    // find_itinerary
    let tickets = vec![
        vec!["MUC".to_string(), "LHR".to_string()],
        vec!["JFK".to_string(), "MUC".to_string()],
        vec!["SFO".to_string(), "SJC".to_string()],
        vec!["LHR".to_string(), "SFO".to_string()],
    ];
    println!("Test: {:?}", find_itinerary::Solution::find_itinerary(tickets));
}
