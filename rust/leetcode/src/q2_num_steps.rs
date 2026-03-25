impl Solution {
    pub fn num_steps(s: String) -> i32 {
        let q = s.as_bytes();
        let mut i = q.len();
        let mut x = 0i32;
        let mut y = 0i32;
        while i > 1 {
            i -= 1;
            let z = ((q[i] & 1) as i32) ^ y;
            x += 1 + (z & 1);
            y |= z;
        }
        x + y
    }
}
