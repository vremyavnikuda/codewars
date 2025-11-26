use std::collections::{BTreeMap, HashMap, HashSet};

struct AllOne {
    m: HashMap<String, usize>,
    f: BTreeMap<usize, HashSet<String>>,
}

impl AllOne {
    fn new() -> Self {
        AllOne {
            m: HashMap::new(),
            f: BTreeMap::new(),
        }
    }

    fn inc(&mut self, key: String) {
        let c = *self.m.get(&key).unwrap_or(&0);

        if c > 0 {
            if let Some(s) = self.f.get_mut(&c) {
                s.remove(&key);
                if s.is_empty() {
                    self.f.remove(&c);
                }
            }
        }

        let nc = c + 1;
        self.m.insert(key.clone(), nc);
        self.f.entry(nc).or_insert_with(HashSet::new).insert(key);
    }

    fn dec(&mut self, key: String) {
        if let Some(&c) = self.m.get(&key) {
            if let Some(s) = self.f.get_mut(&c) {
                s.remove(&key);
                if s.is_empty() {
                    self.f.remove(&c);
                }
            }

            if c == 1 {
                self.m.remove(&key);
            } else {
                let nc = c - 1;
                self.m.insert(key.clone(), nc);
                self.f.entry(nc).or_insert_with(HashSet::new).insert(key);
            }
        }
    }

    fn get_max_key(&self) -> String {
        self.f
            .iter()
            .next_back()
            .and_then(|(_, s)| s.iter().next())
            .cloned()
            .unwrap_or_default()
    }

    fn get_min_key(&self) -> String {
        self.f
            .iter()
            .next()
            .and_then(|(_, s)| s.iter().next())
            .cloned()
            .unwrap_or_default()
    }
}

fn main() {
    let mut obj = AllOne::new();
    obj.inc("hello".to_string());
    obj.inc("hello".to_string());
    println!("getMaxKey(): {}", obj.get_max_key());
    println!("getMinKey(): {}", obj.get_min_key());
    obj.inc("leet".to_string());
    println!("getMaxKey(): {}", obj.get_max_key());
    println!("getMinKey(): {}", obj.get_min_key());
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn t1() {
        let mut obj = AllOne::new();
        obj.inc("hello".to_string());
        obj.inc("hello".to_string());
        assert_eq!(obj.get_max_key(), "hello");
        assert_eq!(obj.get_min_key(), "hello");
        obj.inc("leet".to_string());
        assert_eq!(obj.get_max_key(), "hello");
        assert_eq!(obj.get_min_key(), "leet");
    }

    #[test]
    fn t2() {
        let mut obj = AllOne::new();
        obj.inc("a".to_string());
        obj.inc("b".to_string());
        obj.inc("b".to_string());
        obj.inc("c".to_string());
        obj.inc("c".to_string());
        obj.inc("c".to_string());
        assert_eq!(obj.get_max_key(), "c");
        assert_eq!(obj.get_min_key(), "a");
        obj.dec("b".to_string());
        obj.dec("b".to_string());
        assert_eq!(obj.get_min_key(), "a");
    }

    #[test]
    fn t3() {
        let mut obj = AllOne::new();
        obj.inc("hello".to_string());
        obj.inc("goodbye".to_string());
        obj.inc("hello".to_string());
        obj.inc("hello".to_string());
        assert_eq!(obj.get_max_key(), "hello");
        obj.inc("leet".to_string());
        obj.inc("code".to_string());
        obj.inc("leet".to_string());
        obj.dec("hello".to_string());
        obj.inc("leet".to_string());
        obj.inc("code".to_string());
        obj.inc("code".to_string());
        assert_eq!(obj.get_max_key(), "leet");
    }
}
