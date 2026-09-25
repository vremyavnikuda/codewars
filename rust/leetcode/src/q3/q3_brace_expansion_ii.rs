use std::collections::BTreeSet;

impl Solution {
    pub fn brace_expansion_ii(expression: String) -> Vec<String> {
        fn asd(aa: String, bb: &mut BTreeSet<String>) {
            let Some(cc) = aa.find('}') else {
                bb.insert(aa);
                return;
            };
            let dd = aa[..cc].rfind('{').unwrap();
            for ee in aa[dd + 1..cc].split(',') {
                asd(format!("{}{}{}", &aa[..dd], ee, &aa[cc + 1..]), bb);
            }
        }
        let mut cc = BTreeSet::new();
        asd(expression, &mut cc);
        cc.into_iter().collect()
    }
}

#[cfg(test)]
mod tests {
    use super::*;
    #[test]
    fn t1() {
        assert_eq!(
            Solution::brace_expansion_ii("{a,b}{c,{d,e}}".to_string()),
            vec![
                "ac".to_string(),
                "ad".to_string(),
                "ae".to_string(),
                "bc".to_string(),
                "bd".to_string(),
                "be".to_string()
            ]
        );
    }

    #[test]
    fn t2() {
        assert_eq!(
            Solution::brace_expansion_ii("{{a,z},a{b,c},{ab,z}}".to_string()),
            vec![
                "a".to_string(),
                "ab".to_string(),
                "ac".to_string(),
                "z".to_string()
            ]
        );
    }

    #[test]
    fn t3() {
        assert_eq!(
            Solution::brace_expansion_ii("a{b,c}".to_string()),
            vec!["ab".to_string(), "ac".to_string()]
        );
    }

    #[test]
    fn t4() {
        assert_eq!(
            Solution::brace_expansion_ii("abc".to_string()),
            vec!["abc".to_string()]
        );
    }
}
