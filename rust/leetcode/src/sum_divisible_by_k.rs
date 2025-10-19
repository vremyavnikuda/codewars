use std::collections::HashMap;
struct Solution;
impl Solution {
    pub fn sum_divisible_by_k(nums: Vec<i32>, k: i32) -> i32 {
        let mut freq_map: HashMap<i32, i32> = HashMap::new();

        // Count frequency of each element
        for &num in &nums {
            *freq_map.entry(num).or_insert(0) += 1;
        }

        let mut sum = 0;

        // Sum elements whose frequency is divisible by k
        for (&num, &count) in &freq_map {
            if count % k == 0 {
                sum += num * count;
            }
        }

        sum
    }
}
