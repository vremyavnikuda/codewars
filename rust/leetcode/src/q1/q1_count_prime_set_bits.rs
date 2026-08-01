pub struct Solution;

impl Solution {
    pub fn count_prime_set_bits(left: i32, right: i32) -> i32 {
        if left > right {
            return 0;
        }
        let (mut _0, _1, mut _2) = (left as u32, right as u32, 0i32);
        loop {
            _2 += ((0xA28ACu32 >> _0.count_ones()) & 1) as i32;
            if _0 == _1 {
                break _2;
            }
            _0 += 1;
        }
    }
}

#[cfg(test)]
mod tests {
    use super::Solution;

    #[test]
    fn t0() {
        assert_eq!(Solution::count_prime_set_bits(6, 10), 4);
    }

    #[test]
    fn t1() {
        assert_eq!(Solution::count_prime_set_bits(10, 15), 5);
    }
}
