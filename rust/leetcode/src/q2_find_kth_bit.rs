impl Solution {
    #[inline(always)]
    pub fn find_kth_bit(n: i32, k: i32) -> char {
        let (mut _0, mut _1, mut _2) = ((1_i32) << n, k, 0_u8);
        loop {
            if _1 == 1 {
                return ((_2 ^ 0) + b'0') as char;
            }
            if (_1 & (_1 - 1)) == 0 {
                return ((_2 ^ 1) + b'0') as char;
            }
            let _3 = (_1 << 1) >= (_0 - 1);
            _2 ^= _3 as u8;
            _1 = if _3 { _0 - _1 } else { _1 };
            _0 >>= 1;
        }
    }
}
