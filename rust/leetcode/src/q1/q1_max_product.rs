impl Solution {
    pub fn max_product(n: i32) -> i32 {
        let mut q1 = 0;
        let mut q2 = 0;
        let mut a1 = n.unsigned_abs();
        while a1 > 0 {
            let a2 = (a1 % 10) as i32;
            if q1 < a2 {
                q2 = q1;
                q1 = a2;
            } else if q2 < a2 {
                q2 = a2;
            }
            a1 /= 10;
        }
        q1 * q2
    }
}