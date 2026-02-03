impl Solution {
    pub fn is_trionic(nums: Vec<i32>) -> bool {
        let n = nums.len();
        if n < 3 {
            return false;
        }
        let a = &nums;
        let mut p = 0usize;
        while p < n - 2 && a[p] < a[p + 1] {
            p += 1;
        }
        if p == 0 {
            return false;
        }
        let mut q = p;
        while q < n - 1 && a[q] > a[q + 1] {
            q += 1;
        }
        if q == p || q == n - 1 {
            return false;
        }
        while q < n - 1 && a[q] < a[q + 1] {
            q += 1;
        }
        q == n - 1
    }
}
