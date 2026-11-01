impl Solution {
    pub fn minimum_max_value(n: i32, index: i32, value: i32) -> i64 {
        if value == 1 {
            return -1;
        }
        let (v, left, right) = (value as i64, index as i64, (n - 1 - index) as i64);
        let p = (2..)
            .take_while(|d| d * d <= v)
            .find(|d| v % d == 0)
            .unwrap_or(v);
        if left > 0 && v - p - 2 * (left - 1) < 2 {
            return -1;
        }
        if right == 0 {
            v
        } else {
            v + p + 2 * (right - 1)
        }
    }
}

#[cfg(test)]
mod tests {
    use super::*;
    #[test]
    fn examples() {
        assert_eq!(Solution::minimum_max_value(4, 2, 8), 10);
        assert_eq!(Solution::minimum_max_value(2, 1, 3), -1);
        assert_eq!(Solution::minimum_max_value(2, 0, 3), 6);
    }
}
