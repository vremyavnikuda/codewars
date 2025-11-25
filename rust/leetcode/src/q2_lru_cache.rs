use std::collections::{HashMap, LinkedList};

struct N {
    k: i32,
    v: i32,
    f: usize,
}

struct LFUCache {
    c: usize,
    m: HashMap<i32, (usize, usize)>,
    l: HashMap<usize, LinkedList<N>>,
    f: usize,
}

impl LFUCache {
    fn new(capacity: i32) -> Self {
        LFUCache {
            c: capacity as usize,
            m: HashMap::new(),
            l: HashMap::new(),
            f: 0,
        }
    }

    fn u(&mut self, key: i32) {
        if let Some(&(idx, freq)) = self.m.get(&key) {
            let mut v = 0;
            if let Some(list) = self.l.get_mut(&freq) {
                let mut i = 0;
                for node in list.iter() {
                    if node.k == key {
                        v = node.v;
                        break;
                    }
                    i += 1;
                }
                let mut s = list.split_off(i);
                s.pop_front();
                list.append(&mut s);

                if list.is_empty() && freq == self.f {
                    self.f += 1;
                }
            }

            let nf = freq + 1;
            self.l
                .entry(nf)
                .or_insert_with(LinkedList::new)
                .push_back(N { k: key, v, f: nf });
            self.m.insert(key, (self.l[&nf].len() - 1, nf));
        }
    }

    fn get(&mut self, key: i32) -> i32 {
        if self.c == 0 || !self.m.contains_key(&key) {
            return -1;
        }

        let freq = self.m[&key].1;
        let mut v = -1;

        if let Some(list) = self.l.get(&freq) {
            for node in list.iter() {
                if node.k == key {
                    v = node.v;
                    break;
                }
            }
        }

        self.u(key);
        v
    }

    fn put(&mut self, key: i32, value: i32) {
        if self.c == 0 {
            return;
        }

        if self.m.contains_key(&key) {
            let freq = self.m[&key].1;
            if let Some(list) = self.l.get_mut(&freq) {
                for node in list.iter_mut() {
                    if node.k == key {
                        node.v = value;
                        break;
                    }
                }
            }
            self.u(key);
        } else {
            if self.m.len() >= self.c {
                if let Some(list) = self.l.get_mut(&self.f) {
                    if let Some(node) = list.pop_front() {
                        self.m.remove(&node.k);
                    }
                }
            }

            self.l
                .entry(1)
                .or_insert_with(LinkedList::new)
                .push_back(N {
                    k: key,
                    v: value,
                    f: 1,
                });
            self.m.insert(key, (self.l[&1].len() - 1, 1));
            self.f = 1;
        }
    }
}

fn main() {
    let mut obj = LFUCache::new(2);
    obj.put(1, 1);
    obj.put(2, 2);
    println!("get(1): {}", obj.get(1));
    obj.put(3, 3);
    println!("get(2): {}", obj.get(2));
    println!("get(3): {}", obj.get(3));
    obj.put(4, 4);
    println!("get(1): {}", obj.get(1));
    println!("get(3): {}", obj.get(3));
    println!("get(4): {}", obj.get(4));
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn t1() {
        let mut obj = LFUCache::new(2);
        obj.put(1, 1);
        obj.put(2, 2);
        assert_eq!(obj.get(1), 1);
        obj.put(3, 3);
        assert_eq!(obj.get(2), -1);
        assert_eq!(obj.get(3), 3);
        obj.put(4, 4);
        assert_eq!(obj.get(1), -1);
        assert_eq!(obj.get(3), 3);
        assert_eq!(obj.get(4), 4);
    }

    #[test]
    fn t2() {
        let mut obj = LFUCache::new(0);
        obj.put(0, 0);
        assert_eq!(obj.get(0), -1);
    }

    #[test]
    fn t3() {
        let mut obj = LFUCache::new(2);
        obj.put(2, 1);
        obj.put(3, 2);
        assert_eq!(obj.get(3), 2);
        assert_eq!(obj.get(2), 1);
        obj.put(4, 3);
        assert_eq!(obj.get(2), 1);
        assert_eq!(obj.get(3), -1);
        assert_eq!(obj.get(4), 3);
    }
}
