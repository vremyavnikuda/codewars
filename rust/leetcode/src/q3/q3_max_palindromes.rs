struct Solution;

impl Solution {
    pub fn max_palindromes(s: String, k: i32) -> i32 {
        let aa = s.as_bytes();
        let bb = k.max(1) as usize;
        let mut cc = 0;
        let mut dd = 0usize;
        for ee in 0..aa.len() {
            for ff in [bb, bb + 1] {
                if ee + 1 >= ff && ee + 1 - ff >= dd {
                    let gg = &aa[ee + 1 - ff..=ee];
                    if gg.iter().eq(gg.iter().rev()) {
                        cc += 1;
                        dd = ee + 1;
                        break;
                    }
                }
            }
        }
        cc
    }
}

fn main() {
    println!("{}", Solution::max_palindromes("abaccdbbd".to_string(), 3));
    println!("{}", Solution::max_palindromes("adbcda".to_string(), 2));
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn t1() {
        assert_eq!(Solution::max_palindromes("abaccdbbd".to_string(), 3), 2);
    }

    #[test]
    fn t2() {
        assert_eq!(Solution::max_palindromes("adbcda".to_string(), 2), 0);
    }

    #[test]
    fn t3() {
        assert_eq!(Solution::max_palindromes("aaaaa".to_string(), 1), 5);
        assert_eq!(Solution::max_palindromes("aaaaa".to_string(), 2), 2);
        assert_eq!(Solution::max_palindromes("abcde".to_string(), 5), 0);
    }
}
