use std::cmp::Ordering;

pub struct Solution;

impl Solution {
    pub fn find_kth_largest(mut nums: Vec<i32>, k: i32) -> i32 {
        let n = nums.len();
        let target_idx = n - k as usize;
        Self::quick_select(&mut nums, 0, n - 1, target_idx)
    }
    
    #[inline]
    fn quick_select(nums: &mut [i32], mut left: usize, mut right: usize, target_idx: usize) -> i32 {
        loop {
            if left == right {
                return nums[left];
            }
            
            let pivot_idx = Self::partition(nums, left, right);
            
            match pivot_idx.cmp(&target_idx) {
                Ordering::Equal => return nums[pivot_idx],
                Ordering::Greater => right = pivot_idx - 1,
                Ordering::Less => left = pivot_idx + 1,
            }
        }
    }
    
    #[inline]
    fn partition(nums: &mut [i32], left: usize, right: usize) -> usize {
        let pivot_idx = Self::median_of_three(nums, left, right);
        nums.swap(pivot_idx, right);
        let pivot = nums[right];
        
        let mut i = left;
        
        for j in left..right {
            if nums[j] < pivot {
                nums.swap(i, j);
                i += 1;
            }
        }
        
        nums.swap(i, right);
        i
    }
    
    #[inline]
    fn median_of_three(nums: &[i32], left: usize, right: usize) -> usize {
        let mid = left + (right - left) / 2;
        
        if nums[left] > nums[mid] {
            if nums[mid] > nums[right] {
                mid
            } else if nums[left] > nums[right] {
                right
            } else {
                left
            }
        } else if nums[left] > nums[right] {
            left
        } else if nums[mid] > nums[right] {
            right
        } else {
            mid
        }
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_example_1() {
        assert_eq!(Solution::find_kth_largest(vec![3, 2, 1, 5, 6, 4], 2), 5);
    }

    #[test]
    fn test_example_2() {
        assert_eq!(
            Solution::find_kth_largest(vec![3, 2, 3, 1, 2, 4, 5, 5, 6], 4),
            4
        );
    }

    #[test]
    fn test_single_element() {
        assert_eq!(Solution::find_kth_largest(vec![1], 1), 1);
    }

    #[test]
    fn test_two_elements() {
        assert_eq!(Solution::find_kth_largest(vec![2, 1], 1), 2);
        assert_eq!(Solution::find_kth_largest(vec![2, 1], 2), 1);
    }

    #[test]
    fn test_all_same() {
        assert_eq!(Solution::find_kth_largest(vec![5, 5, 5, 5, 5], 3), 5);
    }

    #[test]
    fn test_largest() {
        assert_eq!(Solution::find_kth_largest(vec![3, 2, 1, 5, 6, 4], 1), 6);
    }

    #[test]
    fn test_smallest() {
        assert_eq!(Solution::find_kth_largest(vec![3, 2, 1, 5, 6, 4], 6), 1);
    }

    #[test]
    fn test_negative_numbers() {
        assert_eq!(
            Solution::find_kth_largest(vec![-1, -2, -3, -4, -5], 2),
            -2
        );
    }

    #[test]
    fn test_mixed_numbers() {
        assert_eq!(
            Solution::find_kth_largest(vec![-5, 0, 5, -3, 3], 3),
            0
        );
    }

    #[test]
    fn test_large_array() {
        let nums: Vec<i32> = (1..=1000).rev().collect();
        assert_eq!(Solution::find_kth_largest(nums, 500), 501);
    }

    #[test]
    fn test_duplicates() {
        assert_eq!(
            Solution::find_kth_largest(vec![1, 2, 2, 3, 3, 3, 4, 4, 4, 4], 5),
            3
        );
    }
}
