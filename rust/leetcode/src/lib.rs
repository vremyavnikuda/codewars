struct Solution;
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
