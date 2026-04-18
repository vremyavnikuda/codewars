impl Solution {
    #[inline(always)]
    pub fn mirror_distance(n: i32) -> i32 {
        let (mut _x, mut _y) = (n as i64, 0i64);
        while _x != 0 {
            _y = ((_y << 3) + (_y << 1)) + _x % 10;
            _x /= 10;
        }
        let _d = (n as i64) - _y;
        ((_d ^ (_d >> 63)) - (_d >> 63)) as i32
    }
}
