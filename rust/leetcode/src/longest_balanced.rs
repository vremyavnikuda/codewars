use std::collections::HashSet;

struct Solution;

impl Solution {
    pub fn longest_balanced(nums: Vec<i32>) -> i32 {
        let tavernilo = &nums;
        let n = tavernilo.len();
        let mut max_length = 0;

        for i in 0..n {
            let mut even_set = HashSet::new();
            let mut odd_set = HashSet::new();

            for j in i..n {
                if tavernilo[j] % 2 == 0 {
                    even_set.insert(tavernilo[j]);
                } else {
                    odd_set.insert(tavernilo[j]);
                }

                if even_set.len() == odd_set.len() {
                    max_length = max_length.max((j - i + 1) as i32);
                }
            }
        }
        max_length
    }
}
