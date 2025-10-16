pub struct Solution;

impl Solution {
    pub fn is_match(s: String, p: String) -> bool {
        let s = s.as_bytes();
        let p = p.as_bytes();
        let m = s.len();
        let n = p.len();
        
        // dp[i][j] = true if first i chars of s match first j chars of p
        let mut dp = vec![vec![false; n + 1]; m + 1];
        
        // Empty string matches empty pattern
        dp[0][0] = true;
        
        // Handle patterns like a*, a*b*, etc. that can match empty string
        for j in 2..=n {
            if p[j - 1] == b'*' {
                dp[0][j] = dp[0][j - 2];
            }
        }
        
        for i in 1..=m {
            for j in 1..=n {
                if p[j - 1] == b'*' {
                    // Star can match zero of preceding element
                    dp[i][j] = dp[i][j - 2];
                    
                    // Or star can match one or more if chars match
                    let prev_char = p[j - 2];
                    if prev_char == b'.' || prev_char == s[i - 1] {
                        dp[i][j] = dp[i][j] || dp[i - 1][j];
                    }
                } else if p[j - 1] == b'.' || p[j - 1] == s[i - 1] {
                    // Current chars match
                    dp[i][j] = dp[i - 1][j - 1];
                }
            }
        }
        
        dp[m][n]
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_example_1() {
        assert_eq!(Solution::is_match("aa".to_string(), "a".to_string()), false);
    }

    #[test]
    fn test_example_2() {
        assert_eq!(Solution::is_match("aa".to_string(), "a*".to_string()), true);
    }

    #[test]
    fn test_example_3() {
        assert_eq!(Solution::is_match("ab".to_string(), ".*".to_string()), true);
    }

    #[test]
    fn test_complex_1() {
        assert_eq!(Solution::is_match("aab".to_string(), "c*a*b".to_string()), true);
    }

    #[test]
    fn test_complex_2() {
        assert_eq!(Solution::is_match("mississippi".to_string(), "mis*is*p*.".to_string()), false);
    }

    #[test]
    fn test_empty() {
        assert_eq!(Solution::is_match("".to_string(), "".to_string()), true);
    }

    #[test]
    fn test_star_at_start() {
        assert_eq!(Solution::is_match("ab".to_string(), ".*c".to_string()), false);
    }

    #[test]
    fn test_multiple_stars() {
        assert_eq!(Solution::is_match("aaa".to_string(), "a*a".to_string()), true);
    }
}
