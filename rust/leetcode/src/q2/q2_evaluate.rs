use std::collections::HashMap;

pub struct Solution;

impl Solution {
    pub fn evaluate(s: String, knowledge: Vec<Vec<String>>) -> String {
        let aa: HashMap<&str, &str> = knowledge
            .iter()
            .map(|bb| (bb[0].as_str(), bb[1].as_str()))
            .collect();
        let mut cc = String::with_capacity(s.len());
        let mut dd = s.as_str();
        while let Some((ee, ff)) = dd.split_once('(') {
            let (gg, asd) = ff.split_once(')').unwrap();
            cc.push_str(ee);
            cc.push_str(aa.get(gg).copied().unwrap_or("?"));
            dd = asd;
        }
        cc.push_str(dd);
        cc
    }
}

#[cfg(test)]
mod tests {
    use super::*;
    #[test]
    fn aa() {
        let bb = |cc: &[[&str; 2]]| {
            cc.iter()
                .map(|dd| dd.iter().map(|ee| ee.to_string()).collect())
                .collect()
        };
        assert_eq!(
            Solution::evaluate(
                "(name)is(age)yearsold".into(),
                bb(&[["name", "bob"], ["age", "two"]])
            ),
            "bobistwoyearsold"
        );
        assert_eq!(
            Solution::evaluate("hi(name)".into(), bb(&[["a", "b"]])),
            "hi?"
        );
        assert_eq!(
            Solution::evaluate("(a)(a)(a)aaa".into(), bb(&[["a", "yes"]])),
            "yesyesyesaaa"
        );
    }
}
