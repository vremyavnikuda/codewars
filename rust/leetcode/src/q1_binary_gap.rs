pub struct Solution;

impl Solution {
    #[inline(always)]
    pub fn binary_gap(n: i32) -> i32 {
        let (mut _0, mut _1, mut _2) = (n as u32, 0u32, 0u32);
        if _0 == 0 {
            return 0;
        }
        _1 = _0.trailing_zeros();
        _0 &= _0.wrapping_sub(1);
        while _0 != 0 {
            let _4 = _0.trailing_zeros();
            _2 ^= (_2 ^ (_4 - _1)) & (0u32.wrapping_sub((_2 < (_4 - _1)) as u32));
            _1 = _4;
            _0 &= _0.wrapping_sub(1);
        }
        _2 as i32
    }
}

#[cfg(test)]
mod tests {
    use super::Solution;

    #[test]
    fn t0() {
        assert_eq!(Solution::binary_gap(22), 2);
    }

    #[test]
    fn t1() {
        assert_eq!(Solution::binary_gap(8), 0);
    }

    #[test]
    fn t2() {
        assert_eq!(Solution::binary_gap(5), 2);
    }

    #[test]
    fn t3() {
        assert_eq!(Solution::binary_gap(1), 0);
    }
}
