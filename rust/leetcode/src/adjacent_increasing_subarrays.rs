pub struct Solution;

impl Solution {
    pub fn max_increasing_subarrays(nums: Vec<i32>) -> i32 {
        let n = nums.len();
        if n < 2 {
            return 0;
        }
        
        let mut lengths = vec![1; n];
        
        for i in (0..n - 1).rev() {
            if nums[i] < nums[i + 1] {
                lengths[i] = lengths[i + 1] + 1;
            }
        }
        
        let mut max_k = 0;
        
        for i in 0..n {
            let current_len = lengths[i];
            
            if current_len >= 2 {
                max_k = max_k.max(current_len / 2);
            }
            
            let next_start = i + current_len;
            if next_start < n {
                let next_len = lengths[next_start];
                let k = current_len.min(next_len);
                if k >= 1 && (current_len >= k && next_len >= k) {
                    max_k = max_k.max(k);
                }
            }
        }
        
        max_k as i32
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_example_1() {
        assert_eq!(
            Solution::max_increasing_subarrays(vec![2, 5, 7, 8, 9, 2, 3, 4, 3, 1]),
            3
        );
    }

    #[test]
    fn test_example_2() {
        assert_eq!(
            Solution::max_increasing_subarrays(vec![1, 2, 3, 4, 4, 4, 4, 5, 6, 7]),
            2
        );
    }

    #[test]
    fn test_minimal() {
        assert_eq!(Solution::max_increasing_subarrays(vec![1, 2]), 1);
    }

    #[test]
    fn test_all_increasing() {
        assert_eq!(Solution::max_increasing_subarrays(vec![1, 2, 3, 4, 5, 6]), 3);
    }

    #[test]
    fn test_decreasing_array() {
        assert_eq!(Solution::max_increasing_subarrays(vec![5, 4, 3, 2, 1]), 1);
    }

    #[test]
    fn test_multiple_segments() {
        assert_eq!(
            Solution::max_increasing_subarrays(vec![1, 2, 3, 1, 2, 3, 4]),
            3
        );
    }

    #[test]
    fn test_long_then_short() {
        assert_eq!(
            Solution::max_increasing_subarrays(vec![1, 2, 3, 4, 5, 10, 11]),
            3
        );
    }

    #[test]
    fn test_all_strictly_increasing() {
        assert_eq!(
            Solution::max_increasing_subarrays(vec![1, 2, 10, 11, 12, 13, 14]),
            3
        );
    }

    #[test]
    fn test_equal_adjacent_segments() {
        assert_eq!(
            Solution::max_increasing_subarrays(vec![1, 2, 3, 4, 10, 11, 12, 13]),
            4
        );
    }

    #[test]
    fn test_single_split() {
        assert_eq!(Solution::max_increasing_subarrays(vec![1, 2, 10, 11]), 2);
    }

    #[test]
    fn test_large_values() {
        assert_eq!(
            Solution::max_increasing_subarrays(vec![-1000000000, 0, 1000000000]),
            1
        );
    }

    #[test]
    fn test_decreasing_then_increasing() {
        assert_eq!(Solution::max_increasing_subarrays(vec![5, 4, 1, 2, 3]), 1);
    }
}
