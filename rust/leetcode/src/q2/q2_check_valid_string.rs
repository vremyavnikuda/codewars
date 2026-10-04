impl Solution {
    pub fn check_valid_string(s: String) -> bool {
        let mut aa = 0usize;
        let mut bb = 0usize;
        for cc in s.bytes() {
            match cc {
                b'(' => {
                    aa += 1;
                    bb += 1;
                }
                b')' => {
                    if bb == 0 {
                        return false;
                    }
                    aa = aa.saturating_sub(1);
                    bb -= 1;
                }
                b'*' => {
                    aa = aa.saturating_sub(1);
                    bb += 1;
                }
                _ => return false,
            }
        }
        aa == 0
    }
}

#[cfg(test)]
mod tests {
    use super::Solution;
    #[test]
    fn checks_wildcards_and_parenthesis_order() {
        for (aa, bb) in [
            ("", true),
            ("()", true),
            ("(*)", true),
            ("(*))", true),
            ("*", true),
            ("***", true),
            ("(*", true),
            ("*)", true),
            ("(", false),
            (")", false),
            (")(", false),
            ("*(", false),
            (")*", false),
            ("((*", false),
            ("(*)))", false),
        ] {
            assert_eq!(Solution::check_valid_string(aa.to_owned()), bb, "{aa}");
        }
    }
}
