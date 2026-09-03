impl Solution {
    pub fn uniform_array(nums1: Vec<i32>) -> bool {
        nums1
            .iter()
            .filter(|aa| *aa % 2 == 1)
            .min()
            .map(|bb| !nums1.iter().any(|cc| cc % 2 == 0 && cc < bb))
            .unwrap_or(true)
    }
}
