impl Solution {
    pub fn count_binary_substrings(s: String) -> i32 {
        let _0 = s.as_bytes();
        let _1 = _0.len();
        let mut _2: usize = 0;
        let mut _3: usize = 0;
        let mut _4: usize = 0;
        while _2 < _1 {
            let mut _5 = _2 + 1;
            while _5 < _1 && _0[_5] == _0[_2] {
                _5 += 1;
            }
            let _6 = _5 - _2;
            _4 += _3.min(_6);
            _3 = _6;
            _2 = _5;
        }
        _4 as i32
    }
}
