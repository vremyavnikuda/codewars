mod longest_balanced_q4;

#[cfg(test)]
mod tests {
    use super::*;

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
