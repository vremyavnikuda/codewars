pub struct Solution;

impl Solution {
    #[inline(always)]
    pub fn concatenated_binary(n: i32) -> i32 {
        let (mut _0, mut _1, _2, mut _3, _4) = (0u64, 0u32, 1_000_000_007u64, 1u64, n as u64);
        while _3 <= _4 {
            _1 += ((_3 & (_3.wrapping_sub(1))) == 0) as u32;
            _0 = ((_0.wrapping_shl(_1) | _3) % _2) as u64;
            _3 = _3.wrapping_add(1);
        }
        _0 as i32
    }
}
