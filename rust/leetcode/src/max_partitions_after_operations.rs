pub struct Solution;

impl Solution {
    pub fn max_partitions_after_operations(s: String, k: i32) -> i32 {
        use std::collections::HashMap;
        
        if k == 26 {
            return 1;
        }
        
        let s_bytes = s.as_bytes();
        let n = s_bytes.len();
        let k = k as u32;
        
        let mut memo: HashMap<u64, i32> = HashMap::new();
        
        fn dfs(
            index: usize,
            char_mask: u32,
            can_change: bool,
            s_bytes: &[u8],
            n: usize,
            k: u32,
            memo: &mut HashMap<u64, i32>
        ) -> i32 {
            if index >= n {
                return 1;
            }
            let state_key = ((index as u64) << 32) | ((char_mask as u64) << 1) | (can_change as u64);
            if let Some(&result) = memo.get(&state_key) {
                return result;
            }
            let current_char_bit = 1 << (s_bytes[index] - b'a');
            let new_char_mask = char_mask | current_char_bit;
            let max_partitions = if new_char_mask.count_ones() > k {
                dfs(index + 1, current_char_bit, can_change, s_bytes, n, k, memo) + 1
            } else {
                dfs(index + 1, new_char_mask, can_change, s_bytes, n, k, memo)
            };
            let mut max_partitions = max_partitions;
            if can_change {
                for letter in 0..26 {
                    let replacement_char_bit = 1 << letter;
                    let new_char_mask = char_mask | replacement_char_bit;
                    let partitions = if new_char_mask.count_ones() > k {
                        dfs(index + 1, replacement_char_bit, false, s_bytes, n, k, memo) + 1
                    } else {
                        dfs(index + 1, new_char_mask, false, s_bytes, n, k, memo)
                    };
                    max_partitions = max_partitions.max(partitions);
                }
            }
            memo.insert(state_key, max_partitions);
            max_partitions
        }
        dfs(0, 0, true, s_bytes, n, k, &mut memo)
    }
}
