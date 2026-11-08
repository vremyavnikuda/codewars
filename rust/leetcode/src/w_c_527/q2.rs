impl Solution {
    pub fn count_suffix(nums: Vec<i32>, target: Vec<i32>) -> i32 {
        let n = nums.len();
        let (mut a, mut b) = (nums.clone(), target.clone());
        a.sort_unstable();
        b.sort_unstable();
        if a != b {
            return 0;
        }
        let p = (0..n).find(|&i| nums[i] != target[i]).unwrap_or(n - 1);
        let mut q = n - 1;
        while q > 0 && target[q - 1] >= target[q] {
            q -= 1;
        }
        if q > p { 0 } else { (p - q + 1) as i32 }
    }
}
