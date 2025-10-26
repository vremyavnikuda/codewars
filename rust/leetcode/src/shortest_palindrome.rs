pub struct Solution;

impl Solution {
    pub fn shortest_palindrome(s: String) -> String {
        if s.is_empty() {
            return s;
        }

        let bytes = s.as_bytes();
        let n = bytes.len();

        let rev_s: Vec<u8> = bytes.iter().copied().rev().collect();

        let mut combined = Vec::with_capacity(2 * n + 1);
        combined.extend_from_slice(bytes);
        combined.push(b'#');
        combined.extend_from_slice(&rev_s);

        let lps = Self::compute_lps(&combined);
        let palindrome_len = lps[combined.len() - 1];

        let mut result = Vec::with_capacity(2 * n - palindrome_len);
        result.extend_from_slice(&rev_s[..n - palindrome_len]);
        result.extend_from_slice(bytes);

        unsafe { String::from_utf8_unchecked(result) }
    }

    #[inline]
    fn compute_lps(pattern: &[u8]) -> Vec<usize> {
        let n = pattern.len();
        let mut lps = vec![0; n];
        let mut len = 0;
        let mut i = 1;

        while i < n {
            if pattern[i] == pattern[len] {
                len += 1;
                lps[i] = len;
                i += 1;
            } else if len != 0 {
                len = lps[len - 1];
            } else {
                lps[i] = 0;
                i += 1;
            }
        }

        lps
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_example_1() {
        assert_eq!(
            Solution::shortest_palindrome("aacecaaa".to_string()),
            "aaacecaaa"
        );
    }

    #[test]
    fn test_example_2() {
        assert_eq!(Solution::shortest_palindrome("abcd".to_string()), "dcbabcd");
    }

    #[test]
    fn test_empty_string() {
        assert_eq!(Solution::shortest_palindrome("".to_string()), "");
    }

    #[test]
    fn test_single_char() {
        assert_eq!(Solution::shortest_palindrome("a".to_string()), "a");
    }

    #[test]
    fn test_already_palindrome() {
        assert_eq!(Solution::shortest_palindrome("aba".to_string()), "aba");
    }

    #[test]
    fn test_all_same() {
        assert_eq!(Solution::shortest_palindrome("aaaa".to_string()), "aaaa");
    }

    #[test]
    fn test_no_palindrome_prefix() {
        assert_eq!(Solution::shortest_palindrome("abc".to_string()), "cbabc");
    }

    #[test]
    fn test_long_string() {
        let result = Solution::shortest_palindrome("abcdefg".to_string());
        assert_eq!(result, "gfedcbabcdefg");
        assert_eq!(result, result.chars().rev().collect::<String>());
    }
}
