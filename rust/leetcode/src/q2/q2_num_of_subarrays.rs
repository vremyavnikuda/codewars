impl Solution {
    pub fn num_of_subarrays(arr: Vec<i32>) -> i32 {
        let mut aa = [1i64, 0i64];
        let mut bb = 0i64;
        let mut cc = 0i64;
        for &dd in &arr {
            cc = (cc + dd as i64) & 1;
            bb = (bb + aa[(cc ^ 1) as usize]) % 1_000_000_007;
            aa[cc as usize] += 1;
        }
        bb as i32
    }
}
