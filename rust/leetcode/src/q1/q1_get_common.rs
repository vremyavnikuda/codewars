impl Solution {
    pub fn get_common(nums1: Vec<i32>, nums2: Vec<i32>) -> i32 {
        use std::cmp::Ordering::*;
        let (mut a, b) = ((0, 0), (nums1.len(), nums2.len()));
        loop {
            if a.0 >= b.0 || a.1 >= b.1 {
                break -1;
            }
            match unsafe { nums1.get_unchecked(a.0).cmp(nums2.get_unchecked(a.1)) } {
                Equal => break unsafe { *nums1.get_unchecked(a.0) },
                Less => a.0 += 1,
                Greater => a.1 += 1,
            }
        }
    }
}
