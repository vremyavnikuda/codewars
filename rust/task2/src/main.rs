use std::collections::HashMap;

fn main() {}
pub fn length_of_longest_substring(s: &str) -> usize {
    let mut last: HashMap<char, usize> = HashMap::new();
    let (mut l, mut max_len) = (0_usize, 0_usize);

    for (r, c) in s.chars().enumerate() {
        if let Some(&prev) = last.get(&c) {
            if prev >= l {
                l = prev + 1;
            }
        }
        last.insert(c, r);
        max_len = max_len.max(r - l + 1);
    }
    max_len
}

#[cfg(test)]
mod tests {
    use super::length_of_longest_substring as f;
    #[test]
    fn examples() {
        assert_eq!(f("abcabcbb"), 3); // "abc"
        assert_eq!(f("bbbbb"), 1); // "b"
        assert_eq!(f("pwwkew"), 3); // "wke"
        assert_eq!(f(""), 0);
        assert_eq!(f("dvdf"), 3); // "vdf"
    }
}
