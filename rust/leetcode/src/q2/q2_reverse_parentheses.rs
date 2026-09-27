pub struct Solution;

impl Solution {
    pub fn reverse_parentheses(s: String) -> String {
        let mut aa = s.into_bytes();
        let mut bb = 0;
        for cc in 0..aa.len() {
            let dd = aa[cc];
            if dd == b')' {
                let ee = aa[..bb].iter().rposition(|&asd| asd == b'(').unwrap();
                aa[ee..bb].reverse();
                bb -= 1;
            } else {
                aa[bb] = dd;
                bb += 1;
            }
        }
        aa.truncate(bb);
        String::from_utf8(aa).unwrap()
    }
}

#[cfg(test)]
mod tests {
    use super::*;
    #[test]
    fn aa() {
        assert_eq!(Solution::reverse_parentheses("(abcd)".into()), "dcba");
        assert_eq!(Solution::reverse_parentheses("(u(love)i)".into()), "iloveu");
        assert_eq!(
            Solution::reverse_parentheses("(ed(et(oc))el)".into()),
            "leetcode"
        );
        assert_eq!(
            Solution::reverse_parentheses("a(bcdefghijkl(mno)p)q".into()),
            "apmnolkjihgfedcbq"
        );
    }
}
