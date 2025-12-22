struct Solution;

impl Solution {
    pub fn min_deletion_size(strs: Vec<String>) -> i32 {
        let n = strs[0].len();
        let mut f = vec![1; n];

        for i in 1..n {
            for j in 0..i {
                if strs.iter().all(|s| {
                    let b = s.as_bytes();
                    b[j] <= b[i]
                }) {
                    f[i] = f[i].max(f[j] + 1);
                }
            }
        }

        n as i32 - *f.iter().max().unwrap()
    }
}

fn main() {
    let r1 = Solution::min_deletion_size(vec!["babca".to_string(), "bbazb".to_string()]);
    let r2 = Solution::min_deletion_size(vec!["edcba".to_string()]);

    println!("{}", r1);
    println!("{}", r2);
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn t1() {
        assert_eq!(
            Solution::min_deletion_size(vec!["babca".to_string(), "bbazb".to_string(),]),
            3
        );
    }

    #[test]
    fn t2() {
        assert_eq!(Solution::min_deletion_size(vec!["edcba".to_string(),]), 4);
    }

    #[test]
    fn t3() {
        assert_eq!(
            Solution::min_deletion_size(vec![
                "ghi".to_string(),
                "def".to_string(),
                "abc".to_string(),
            ]),
            0
        );
    }
}
