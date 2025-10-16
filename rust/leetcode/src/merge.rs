impl Solution {
    pub fn merge(nums1: &mut Vec<i32>, m: i32, nums2: &mut Vec<i32>, n: i32) {
        let mut i = m as usize;
        let mut j = n as usize;
        let mut k = (m + n) as usize - 1;
        
        while i > 0 && j > 0 {
            if nums1[i - 1] > nums2[j - 1] {
                nums1[k] = nums1[i - 1];
                i -= 1;
            } else {
                nums1[k] = nums2[j - 1];
                j -= 1;
            }
            k -= 1;
        }
        
        while j > 0 {
            nums1[k] = nums2[j - 1];
            j -= 1;
            k -= 1;
        }
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_example_1() {
        let mut nums1 = vec![1, 2, 3, 0, 0, 0];
        let m = 3;
        let mut nums2 = vec![2, 5, 6];
        let n = 3;
        Solution::merge(&mut nums1, m, &mut nums2, n);
        assert_eq!(nums1, vec![1, 2, 2, 3, 5, 6]);
    }

    #[test]
    fn test_example_2() {
        let mut nums1 = vec![1];
        let m = 1;
        let mut nums2 = vec![];
        let n = 0;
        Solution::merge(&mut nums1, m, &mut nums2, n);
        assert_eq!(nums1, vec![1]);
    }

    #[test]
    fn test_example_3() {
        let mut nums1 = vec![0];
        let m = 0;
        let mut nums2 = vec![1];
        let n = 1;
        Solution::merge(&mut nums1, m, &mut nums2, n);
        assert_eq!(nums1, vec![1]);
    }

    #[test]
    fn test_empty_nums2() {
        let mut nums1 = vec![2, 0];
        let m = 1;
        let mut nums2 = vec![];
        let n = 0;
        Solution::merge(&mut nums1, m, &mut nums2, n);
        assert_eq!(nums1, vec![2]);
    }

    #[test]
    fn test_single_elements() {
        let mut nums1 = vec![0];
        let m = 0;
        let mut nums2 = vec![1];
        let n = 1;
        Solution::merge(&mut nums1, m, &mut nums2, n);
        assert_eq!(nums1, vec![1]);
    }
}