pub struct Solution;

impl Solution {
    pub fn min_insertions(s: String) -> i32 {
        let mut aa = 0;
        let mut bb = 0;
        let mut cc = s.bytes().peekable();
        while let Some(dd) = cc.next() {
            if dd == b'(' {
                bb += 1;
            } else {
                if cc.next_if_eq(&b')').is_none() {
                    aa += 1;
                }
                if bb == 0 {
                    aa += 1;
                } else {
                    bb -= 1;
                }
            }
        }
        aa + bb * 2
    }
}

#[cfg(test)]
mod tests {
    use super::Solution;
    #[test]
    fn min_insertions_handles_pairs_and_missing_brackets() {
        for (aa, bb) in [
            ("", 0),
            ("(", 2),
            (")", 2),
            ("))", 1),
            ("())", 0),
            ("(()))", 1),
            ("))())(", 3),
            ("(((((", 10),
            (")))))))", 5),
            ("()()", 2),
        ] {
            assert_eq!(Solution::min_insertions(aa.into()), bb, "{aa}");
        }
    }
}
