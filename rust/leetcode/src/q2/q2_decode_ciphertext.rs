impl Solution {
    pub fn decode_ciphertext(encoded_text: String, rows: i32) -> String {
        let _r = rows as usize;
        let _n = encoded_text.len();
        if (_r == 0) | (_n == 0) {
            return String::new();
        }
        let _s = encoded_text.into_bytes();
        let _c = _n / _r;
        if _c == 0 {
            return String::new();
        }
        let mut _o: Vec<u8> = Vec::with_capacity(_n);
        let mut _k = 0usize;
        unsafe {
            let _p = _s.as_ptr();
            let _q = _o.as_mut_ptr();
            let mut _j = 0usize;
            while _j < _c {
                let mut _x = 0usize;
                let mut _y = _j;
                while (_x < _r) & (_y < _c) {
                    *_q.add(_k) = *_p.add(_x * _c + _y);
                    _k += 1;
                    _x += 1;
                    _y += 1;
                }
                _j += 1;
            }
            _o.set_len(_k);
        }
        while !_o.is_empty() && unsafe { *_o.get_unchecked(_o.len() - 1) == b' ' } {
            _o.pop();
        }
        unsafe { String::from_utf8_unchecked(_o) }
    }
}
