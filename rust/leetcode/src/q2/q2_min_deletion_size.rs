struct Solution;

impl Solution {
    pub fn min_deletion_size(strs: Vec<String>) -> i32 {
        let n = strs.len();
        let m = strs[0].len();
        let mut st = vec![false; n - 1];
        let mut a = 0;

        for j in 0..m {
            let mut d = false;

            for i in 0..(n - 1) {
                if !st[i] && strs[i].as_bytes()[j] > strs[i + 1].as_bytes()[j] {
                    d = true;
                    break;
                }
            }

            if d {
                a += 1;
            } else {
                for i in 0..(n - 1) {
                    if !st[i] && strs[i].as_bytes()[j] < strs[i + 1].as_bytes()[j] {
                        st[i] = true;
                    }
                }
            }
        }

        a
    }
}

fn main() {
    let r1 =
        Solution::min_deletion_size(vec!["ca".to_string(), "bb".to_string(), "ac".to_string()]);
    let r2 =
        Solution::min_deletion_size(vec!["xc".to_string(), "yb".to_string(), "za".to_string()]);

    println!("{}", r1);
    println!("{}", r2);
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn t1() {
        assert_eq!(
            Solution::min_deletion_size(
                vec!["ca".to_string(), "bb".to_string(), "ac".to_string(),]
            ),
            1
        );
    }

    #[test]
    fn t2() {
        assert_eq!(
            Solution::min_deletion_size(
                vec!["xc".to_string(), "yb".to_string(), "za".to_string(),]
            ),
            0
        );
    }

    #[test]
    fn t3() {
        assert_eq!(
            Solution::min_deletion_size(vec![
                "zyx".to_string(),
                "wvu".to_string(),
                "tsr".to_string(),
            ]),
            3
        );
    }
}
