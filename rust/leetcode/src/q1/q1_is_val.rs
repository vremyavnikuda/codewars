impl Solution {
    pub fn is_valid(s: String) -> bool {
        let mut aa = s.into_bytes();
        let mut bb = 0;
        for cc in 0..aa.len() {
            let dd = match aa[cc] {
                b'(' => b')',
                b'[' => b']',
                b'{' => b'}',
                dd => {
                    if bb == 0 || aa[bb - 1] != dd {
                        return false;
                    }
                    bb -= 1;
                    continue;
                }
            };
            aa[bb] = dd;
            bb += 1;
        }
        bb == 0
    }
}

#[cfg(test)]
mod tests {
    use super::Solution;
    #[test]
    fn checks_nesting_and_order() {
        assert!(Solution::is_valid("{[()]}".to_string()));
        assert!(Solution::is_valid("()[]{}".to_string()));
        assert!(Solution::is_valid(String::new()));
        assert!(!Solution::is_valid("([)]".to_string()));
        assert!(!Solution::is_valid("({}".to_string()));
        assert!(!Solution::is_valid(")".to_string()));
    }
}
