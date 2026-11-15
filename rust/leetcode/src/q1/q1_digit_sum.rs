impl Solution {
    pub fn digit_sum(s: String, k: i32) -> String {
        let aa = k as usize;
        let mut bb = s;
        while bb.len() > aa {
            bb = bb
                .as_bytes()
                .chunks(aa)
                .map(|cc| {
                    cc.iter()
                        .fold(0, |dd, &ee| dd + (ee - b'0') as i32)
                        .to_string()
                })
                .collect();
        }
        bb
    }
}

#[cfg(test)]
mod tests {
    use super::Solution;

    #[test]
    fn aa() {
        assert_eq!(Solution::digit_sum("11111222223".into(), 3), "135");
        assert_eq!(Solution::digit_sum("00000000".into(), 3), "000");
    }
}
