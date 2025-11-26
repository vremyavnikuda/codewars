use rand::Rng;
use std::collections::{HashMap, HashSet};

struct RandomizedCollection {
    m: HashMap<i32, HashSet<usize>>,
    v: Vec<i32>,
}

impl RandomizedCollection {
    fn new() -> Self {
        RandomizedCollection {
            m: HashMap::new(),
            v: Vec::new(),
        }
    }

    fn insert(&mut self, val: i32) -> bool {
        let r = !self.m.contains_key(&val);
        self.v.push(val);
        self.m
            .entry(val)
            .or_insert_with(HashSet::new)
            .insert(self.v.len() - 1);
        r
    }

    fn remove(&mut self, val: i32) -> bool {
        if let Some(s) = self.m.get_mut(&val) {
            let &i = s.iter().next().unwrap();
            s.remove(&i);
            if s.is_empty() {
                self.m.remove(&val);
            }

            let l = *self.v.last().unwrap();
            let li = self.v.len() - 1;

            self.v[i] = l;
            self.v.pop();

            if i < self.v.len() {
                if let Some(s) = self.m.get_mut(&l) {
                    s.remove(&li);
                    s.insert(i);
                }
            }

            true
        } else {
            false
        }
    }

    fn get_random(&self) -> i32 {
        let i = rand::thread_rng().gen_range(0..self.v.len());
        self.v[i]
    }
}

fn main() {
    let mut obj = RandomizedCollection::new();
    println!("insert(1): {}", obj.insert(1));
    println!("insert(1): {}", obj.insert(1));
    println!("insert(2): {}", obj.insert(2));
    println!("getRandom(): {}", obj.get_random());
    println!("remove(1): {}", obj.remove(1));
    println!("getRandom(): {}", obj.get_random());
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn t1() {
        let mut obj = RandomizedCollection::new();
        assert_eq!(obj.insert(1), true);
        assert_eq!(obj.insert(1), false);
        assert_eq!(obj.insert(2), true);
        let r = obj.get_random();
        assert!(r == 1 || r == 2);
        assert_eq!(obj.remove(1), true);
        let r = obj.get_random();
        assert!(r == 1 || r == 2);
    }

    #[test]
    fn t2() {
        let mut obj = RandomizedCollection::new();
        assert_eq!(obj.insert(4), true);
        assert_eq!(obj.insert(3), true);
        assert_eq!(obj.insert(4), false);
        assert_eq!(obj.insert(2), true);
        assert_eq!(obj.insert(4), false);
        assert_eq!(obj.remove(4), true);
        assert_eq!(obj.remove(3), true);
        assert_eq!(obj.remove(4), true);
        assert_eq!(obj.remove(4), true);
    }

    #[test]
    fn t3() {
        let mut obj = RandomizedCollection::new();
        assert_eq!(obj.insert(1), true);
        assert_eq!(obj.insert(1), false);
        assert_eq!(obj.insert(2), true);
        assert_eq!(obj.insert(1), false);
        assert_eq!(obj.insert(2), false);
        assert_eq!(obj.remove(1), true);
        assert_eq!(obj.remove(2), true);
        assert_eq!(obj.remove(2), true);
        assert_eq!(obj.remove(1), true);
    }
}
