use std::collections::HashSet;

struct Solution;

impl Solution {
    pub fn validate_coupons(
        code: Vec<String>,
        business_line: Vec<String>,
        is_active: Vec<bool>,
    ) -> Vec<String> {
        let bs: HashSet<&str> = ["electronics", "grocery", "pharmacy", "restaurant"]
            .iter()
            .copied()
            .collect();

        let mut idx = Vec::new();

        for i in 0..code.len() {
            let c = &code[i];
            let b = &business_line[i];
            let a = is_active[i];

            if a && bs.contains(b.as_str()) && Self::check(c) {
                idx.push(i);
            }
        }

        idx.sort_by(|&i, &j| {
            if business_line[i] != business_line[j] {
                business_line[i].cmp(&business_line[j])
            } else {
                code[i].cmp(&code[j])
            }
        });

        idx.into_iter().map(|i| code[i].clone()).collect()
    }

    fn check(s: &str) -> bool {
        if s.is_empty() {
            return false;
        }

        s.chars().all(|c| c.is_alphanumeric() || c == '_')
    }
}

fn main() {
    let r1 = Solution::validate_coupons(
        vec![
            "ABC123".to_string(),
            "XYZ_456".to_string(),
            "INV@LID".to_string(),
        ],
        vec![
            "electronics".to_string(),
            "grocery".to_string(),
            "pharmacy".to_string(),
        ],
        vec![true, true, true],
    );
    println!("{:?}", r1);
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn t1() {
        assert_eq!(
            Solution::validate_coupons(
                vec![
                    "ABC123".to_string(),
                    "XYZ_456".to_string(),
                    "INV@LID".to_string(),
                ],
                vec![
                    "electronics".to_string(),
                    "grocery".to_string(),
                    "pharmacy".to_string(),
                ],
                vec![true, true, true],
            ),
            vec!["ABC123".to_string(), "XYZ_456".to_string()]
        );
    }

    #[test]
    fn t2() {
        assert_eq!(
            Solution::validate_coupons(
                vec!["CODE1".to_string(), "CODE2".to_string()],
                vec!["electronics".to_string(), "electronics".to_string()],
                vec![true, false],
            ),
            vec!["CODE1".to_string()]
        );
    }

    #[test]
    fn t3() {
        assert_eq!(
            Solution::validate_coupons(
                vec![
                    "G1".to_string(),
                    "E1".to_string(),
                    "G2".to_string(),
                    "E2".to_string(),
                ],
                vec![
                    "grocery".to_string(),
                    "electronics".to_string(),
                    "grocery".to_string(),
                    "electronics".to_string(),
                ],
                vec![true, true, true, true],
            ),
            vec![
                "E1".to_string(),
                "E2".to_string(),
                "G1".to_string(),
                "G2".to_string(),
            ]
        );
    }
}
