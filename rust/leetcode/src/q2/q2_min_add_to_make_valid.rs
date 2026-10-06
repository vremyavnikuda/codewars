impl Solution {
    pub fn min_add_to_make_valid(s: String) -> i32 {
        let (aa, bb) = s.bytes().fold((0, 0), |(aa, bb), cc| {
            if cc == b'(' {
                (aa, bb + 1)
            } else if bb > 0 {
                (aa, bb - 1)
            } else {
                (aa + 1, bb)
            }
        });
        aa + bb
    }
}

#[cfg(test)]
mod tests {
    use super::*;
    #[test]
    fn aa() {
        for (aa, bb) in [
            ("())", 1),
            ("(((", 3),
            ("()", 0),
            ("()))((", 4),
            ("", 0),
            (")", 1),
            ("(", 1),
            (")(", 2),
        ] {
            assert_eq!(Solution::min_add_to_make_valid(aa.into()), bb);
        }
    }
}
