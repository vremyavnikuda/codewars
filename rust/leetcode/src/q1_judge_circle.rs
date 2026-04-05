impl Solution {
    pub fn judge_circle(moves: String) -> bool {
        let _0 = moves.as_bytes();
        let _1 = _0.len();
        let mut _2 = 0usize;
        let mut _3 = 0i64;

        while _2 < _1 {
            let _4 = unsafe { *_0.get_unchecked(_2) };
            _3 += (_4 == b'R') as i64 - (_4 == b'L') as i64;
            _3 += ((_4 == b'U') as i64 - (_4 == b'D') as i64) << 32;
            _2 += 1;
        }

        _3 == 0
    }
}
