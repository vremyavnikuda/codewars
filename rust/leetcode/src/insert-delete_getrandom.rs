use rand::Rng;
use std::collections::HashMap;

struct RandomizedSet {
    m: HashMap<i32, usize>,
    v: Vec<i32>,
}

impl RandomizedSet {
    fn new() -> Self {
        RandomizedSet {
            m: HashMap::new(),
            v: Vec::new(),
        }
    }

    fn insert(&mut self, val: i32) -> bool {
        if self.m.contains_key(&val) {
            return false;
        }

        self.v.push(val);
        self.m.insert(val, self.v.len() - 1);
        true
    }

    fn remove(&mut self, val: i32) -> bool {
        if let Some(&i) = self.m.get(&val) {
            let l = *self.v.last().unwrap();
            self.v[i] = l;
            self.m.insert(l, i);
            self.v.pop();
            self.m.remove(&val);
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
    let mut obj = RandomizedSet::new();
    println!("insert(1): {}", obj.insert(1));
    println!("remove(2): {}", obj.remove(2));
    println!("insert(2): {}", obj.insert(2));
    println!("getRandom(): {}", obj.get_random());
    println!("remove(1): {}", obj.remove(1));
    println!("insert(2): {}", obj.insert(2));
    println!("getRandom(): {}", obj.get_random());
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn t1() {
        let mut obj = RandomizedSet::new();
        assert_eq!(obj.insert(1), true);
        assert_eq!(obj.remove(2), false);
        assert_eq!(obj.insert(2), true);
        let r = obj.get_random();
        assert!(r == 1 || r == 2);
        assert_eq!(obj.remove(1), true);
        assert_eq!(obj.insert(2), false);
        assert_eq!(obj.get_random(), 2);
    }

    #[test]
    fn t2() {
        let mut obj = RandomizedSet::new();
        assert_eq!(obj.insert(0), true);
        assert_eq!(obj.insert(1), true);
        assert_eq!(obj.remove(0), true);
        assert_eq!(obj.insert(2), true);
        assert_eq!(obj.remove(1), true);
        assert_eq!(obj.get_random(), 2);
    }

    #[test]
    fn t3() {
        let mut obj = RandomizedSet::new();
        assert_eq!(obj.insert(3), true);
        assert_eq!(obj.insert(3), false);
        assert_eq!(obj.get_random(), 3);
        assert_eq!(obj.remove(3), true);
        assert_eq!(obj.insert(0), true);
    }
}
