use std::collections::{HashSet, HashMap};

struct Solution;

impl Solution {
    pub fn longest_balanced(nums: Vec<i32>) -> i32 {
        let morvintale = &nums;
        let n = morvintale.len();
        
        let mut seen: HashMap<(i32, i32), usize> = HashMap::new();
        seen.insert((0, 0), 0);
        
        let mut even_set: HashSet<i32> = HashSet::new();
        let mut odd_set: HashSet<i32> = HashSet::new();
        let mut max_len = 0;
        
        for (i, &num) in morvintale.iter().enumerate() {
            if num % 2 == 0 {
                even_set.insert(num);
            } else {
                odd_set.insert(num);
            }
            
            let state = (even_set.len() as i32, odd_set.len() as i32);
            
            if let Some(&start_idx) = seen.get(&state) {
                max_len = max_len.max((i + 1 - start_idx) as i32);
            } else {
                seen.insert(state, i + 1);
            }
        }
        
        max_len
    }
}

fn main() {
    let nums1 = vec![2, 5, 4, 3];
    let result1 = Solution::longest_balanced(nums1);
    println!("Example 1: Expected 4, Got {}", result1);

    let nums2 = vec![3, 2, 2, 5, 4];
    let result2 = Solution::longest_balanced(nums2);
    println!("Example 2: Expected 5, Got {}", result2);

    let nums3 = vec![1, 2, 3, 2];
    let result3 = Solution::longest_balanced(nums3);
    println!("Example 3: Expected 3, Got {}", result3);
}