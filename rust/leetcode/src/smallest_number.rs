impl Solution {
    pub fn smallest_number(n: i32) -> i32 {
        let mut n2 = 1;
        while n2 - 1 < n {
            n2 <<= 1;
        }
        n2 - 1
    }
}
