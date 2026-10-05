impl Solution {
    pub fn score_of_parentheses(s: String) -> i32 {
        let (mut aa, mut bb, mut cc) = (0, 0, b')');
        for dd in s.bytes() {
            if dd == b'(' {
                bb += 1;
            } else {
                bb -= 1;
                if cc == b'(' {
                    aa += 1 << bb;
                }
            }
            cc = dd;
        }
        aa
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn aa() {
        for (aa, bb) in [
            ("()", 1),
            ("(())", 2),
            ("()()", 2),
            ("(()(()))", 6),
            ("((()))", 4),
            ("()(())", 3),
            ("((((((((((((((((((((((((()))))))))))))))))))))))))", 1 << 24),
        ] {
            assert_eq!(Solution::score_of_parentheses(aa.into()), bb);
        }
    }
}
