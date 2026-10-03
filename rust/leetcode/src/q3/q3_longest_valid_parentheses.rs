impl Solution {
    pub fn longest_valid_parentheses(s: String) -> i32 {
        let (mut aa, mut bb, mut cc) = (0, 0, 0);
        for dd in s.bytes() {
            if dd == b'(' {
                aa += 1;
            } else {
                bb += 1;
            }
            if aa == bb {
                cc = cc.max(2 * bb);
            } else if bb > aa {
                aa = 0;
                bb = 0;
            }
        }
        aa = 0;
        bb = 0;
        for dd in s.bytes().rev() {
            if dd == b'(' {
                aa += 1;
            } else {
                bb += 1;
            }
            if aa == bb {
                cc = cc.max(2 * aa);
            } else if aa > bb {
                aa = 0;
                bb = 0;
            }
        }
        cc
    }
}

#[cfg(test)]
mod tests {
    use super::Solution;
    #[test]
    fn handles_unmatched_nested_and_adjacent_parentheses() {
        for (aa, bb) in [
            ("", 0),
            ("(", 0),
            (")", 0),
            ("(((", 0),
            (")))", 0),
            ("()", 2),
            ("(()", 2),
            (")()())", 4),
            ("()(())", 6),
            ("(()())", 6),
            ("())(())", 4),
            ("(()(()", 2),
        ] {
            assert_eq!(Solution::longest_valid_parentheses(aa.into()), bb, "{aa}");
        }
    }
}
