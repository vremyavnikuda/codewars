impl Solution {
    pub fn max_frequency(nums: Vec<i32>, k: i32, num_operations: i32) -> i32 {
        use std::collections::{BTreeMap, HashMap};

        let mut frequency_map: HashMap<i32, i32> = HashMap::new();

        let mut range_difference: BTreeMap<i32, i32> = BTreeMap::new();

        for &num in &nums {
            *frequency_map.entry(num).or_insert(0) += 1;
            range_difference.entry(num).or_insert(0);
            *range_difference.entry(num - k).or_insert(0) += 1;
            *range_difference.entry(num + k + 1).or_insert(0) -= 1;
        }
        let mut max_result = 0;
        let mut current_range_count = 0;
        for (&position, &difference) in &range_difference {
            current_range_count += difference;
            let existing_count = *frequency_map.get(&position).unwrap_or(&0);
            max_result = max_result.max(current_range_count.min(existing_count + num_operations));
        }
        max_result
    }
}