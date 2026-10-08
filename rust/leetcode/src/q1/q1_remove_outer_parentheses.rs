impl Solution {
    pub fn remove_outer_parentheses(s: String) -> String {
        let mut aa = s;
        let mut bb = 0;
        aa.retain(|cc| {
            if cc == '(' {
                bb += 1;
                bb > 1
            } else {
                bb -= 1;
                bb > 0
            }
        });
        aa
    }
}

#[cfg(test)]
mod tests {
    use super::Solution;

    #[test]
    fn removes_outer_parentheses_in_place() {
        for (aa, bb) in [
            ("(()())(())", "()()()"),
            ("(()())(())(()(()))", "()()()()(())"),
            ("()()", ""),
            ("((()))", "(())"),
            ("()", ""),
            ("", ""),
        ] {
            let cc = aa.to_owned();
            let dd = cc.as_ptr();
            let ee = cc.capacity();
            let ff = Solution::remove_outer_parentheses(cc);
            assert_eq!(ff, bb);
            assert_eq!(ff.as_ptr(), dd);
            assert_eq!(ff.capacity(), ee);
        }
    }
}
