impl Solution {
    pub fn max_sum_of_squares(num: i32, sum: i32) -> String {
        if i64::from(num) * 9 < i64::from(sum) {
            return String::new();
        }

        let mut aa = vec![b'0'; num as usize];
        let bb = (sum / 9) as usize;
        aa[..bb].fill(b'9');
        if sum % 9 > 0 {
            aa[bb] += (sum % 9) as u8;
        }
        String::from_utf8(aa).unwrap()
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn maximizes_digits_and_handles_boundaries() {
        for (aa, bb, cc) in [
            (3, 20, "992"),
            (4, 10, "9100"),
            (3, 18, "990"),
            (2, 18, "99"),
            (2, 19, ""),
            (1, 5, "5"),
            (3, 0, "000"),
            (0, 0, ""),
        ] {
            assert_eq!(Solution::max_sum_of_squares(aa, bb), cc);
        }
    }
}
