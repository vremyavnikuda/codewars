use std::collections::HashMap;

#[derive(Default)]
struct T {
    c: HashMap<char, T>,
    e: bool,
}

impl T {
    fn i(&mut self, w: &str) {
        let mut n = self;
        for ch in w.chars().rev() {
            n = n.c.entry(ch).or_default();
        }
        n.e = true;
    }
}

struct StreamChecker {
    t: T,
    s: Vec<char>,
    m: usize,
}

impl StreamChecker {
    fn new(words: Vec<String>) -> Self {
        let mut t = T::default();
        let mut m = 0;

        for w in &words {
            t.i(w);
            m = m.max(w.len());
        }

        StreamChecker {
            t,
            s: Vec::new(),
            m,
        }
    }

    fn query(&mut self, letter: char) -> bool {
        self.s.push(letter);

        if self.s.len() > self.m {
            self.s.remove(0);
        }

        let mut n = &self.t;
        for &ch in self.s.iter().rev() {
            if let Some(next) = n.c.get(&ch) {
                if next.e {
                    return true;
                }
                n = next;
            } else {
                break;
            }
        }

        false
    }
}

fn main() {
    let mut obj = StreamChecker::new(vec!["cd".to_string(), "f".to_string(), "kl".to_string()]);

    let q = vec!['a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l'];
    for ch in q {
        println!("query('{}'): {}", ch, obj.query(ch));
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn t1() {
        let mut obj = StreamChecker::new(vec!["cd".to_string(), "f".to_string(), "kl".to_string()]);

        assert_eq!(obj.query('a'), false);
        assert_eq!(obj.query('b'), false);
        assert_eq!(obj.query('c'), false);
        assert_eq!(obj.query('d'), true);
        assert_eq!(obj.query('e'), false);
        assert_eq!(obj.query('f'), true);
        assert_eq!(obj.query('g'), false);
        assert_eq!(obj.query('h'), false);
        assert_eq!(obj.query('i'), false);
        assert_eq!(obj.query('j'), false);
        assert_eq!(obj.query('k'), false);
        assert_eq!(obj.query('l'), true);
    }

    #[test]
    fn t2() {
        let mut obj = StreamChecker::new(vec![
            "ab".to_string(),
            "ba".to_string(),
            "aaab".to_string(),
            "abab".to_string(),
            "baa".to_string(),
        ]);

        assert_eq!(obj.query('a'), false);
        assert_eq!(obj.query('a'), false);
        assert_eq!(obj.query('a'), false);
        assert_eq!(obj.query('a'), false);
        assert_eq!(obj.query('a'), false);
        assert_eq!(obj.query('b'), true);
        assert_eq!(obj.query('a'), true);
        assert_eq!(obj.query('b'), true);
    }
}
