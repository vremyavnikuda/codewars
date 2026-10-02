impl Solution {
    pub fn generate_parenthesis(n: i32) -> Vec<String> {
        fn aa(bb: i32, cc: i32, dd: &mut String, ee: &mut Vec<String>) {
            if bb == 0 && cc == 0 {
                ee.push(dd.clone());
                return;
            }
            if bb > 0 {
                dd.push('(');
                aa(bb - 1, cc, dd, ee);
                dd.pop();
            }
            if cc > bb {
                dd.push(')');
                aa(bb, cc - 1, dd, ee);
                dd.pop();
            }
        }

        let mut bb = Vec::new();
        if n < 0 {
            return bb;
        }
        let mut cc = String::with_capacity(n as usize * 2);
        aa(n, n, &mut cc, &mut bb);
        bb
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn aa() {
        assert_eq!(Solution::generate_parenthesis(-1), Vec::<String>::new());
        assert_eq!(Solution::generate_parenthesis(0), [""]);
        assert_eq!(Solution::generate_parenthesis(1), ["()"]);
        assert_eq!(Solution::generate_parenthesis(2), ["(())", "()()"]);
        assert_eq!(
            Solution::generate_parenthesis(3),
            ["((()))", "(()())", "(())()", "()(())", "()()()"]
        );
        let aa = Solution::generate_parenthesis(8);
        assert_eq!(aa.len(), 1430);
        assert!(aa.windows(2).all(|bb| bb[0] < bb[1]));
        for bb in &aa {
            assert_eq!(bb.len(), 16);
            let mut cc = 0;
            for dd in bb.bytes() {
                cc += match dd {
                    b'(' => 1,
                    b')' => -1,
                    _ => panic!("unexpected character"),
                };
                assert!(cc >= 0);
            }
            assert_eq!(cc, 0);
        }
    }
}
