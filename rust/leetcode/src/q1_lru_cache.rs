use std::cell::RefCell;
use std::collections::HashMap;
use std::rc::Rc;

type N = Rc<RefCell<Node>>;

struct Node {
    k: i32,
    v: i32,
    p: Option<N>,
    n: Option<N>,
}

impl Node {
    fn new(k: i32, v: i32) -> N {
        Rc::new(RefCell::new(Node {
            k,
            v,
            p: None,
            n: None,
        }))
    }
}

struct LRUCache {
    c: usize,
    m: HashMap<i32, N>,
    h: N,
    t: N,
}

impl LRUCache {
    fn new(capacity: i32) -> Self {
        let h = Node::new(0, 0);
        let t = Node::new(0, 0);
        h.borrow_mut().n = Some(t.clone());
        t.borrow_mut().p = Some(h.clone());

        LRUCache {
            c: capacity as usize,
            m: HashMap::new(),
            h,
            t,
        }
    }

    fn r(&mut self, node: &N) {
        let p = node.borrow().p.clone().unwrap();
        let n = node.borrow().n.clone().unwrap();
        p.borrow_mut().n = Some(n.clone());
        n.borrow_mut().p = Some(p);
    }

    fn a(&mut self, node: &N) {
        let f = self.h.borrow().n.clone().unwrap();
        node.borrow_mut().n = Some(f.clone());
        node.borrow_mut().p = Some(self.h.clone());
        self.h.borrow_mut().n = Some(node.clone());
        f.borrow_mut().p = Some(node.clone());
    }

    fn get(&mut self, key: i32) -> i32 {
        if let Some(node) = self.m.get(&key) {
            let node = node.clone();
            let v = node.borrow().v;
            self.r(&node);
            self.a(&node);
            v
        } else {
            -1
        }
    }

    fn put(&mut self, key: i32, value: i32) {
        if let Some(node) = self.m.get(&key) {
            let node = node.clone();
            node.borrow_mut().v = value;
            self.r(&node);
            self.a(&node);
        } else {
            let node = Node::new(key, value);
            self.m.insert(key, node.clone());
            self.a(&node);

            if self.m.len() > self.c {
                let l = self.t.borrow().p.clone().unwrap();
                let k = l.borrow().k;
                self.m.remove(&k);
                self.r(&l);
            }
        }
    }
}

fn main() {
    let mut obj = LRUCache::new(2);
    obj.put(1, 1);
    obj.put(2, 2);
    println!("get(1): {}", obj.get(1));
    obj.put(3, 3);
    println!("get(2): {}", obj.get(2));
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
        let mut obj = LRUCache::new(2);
        obj.put(1, 1);
        obj.put(2, 2);
        assert_eq!(obj.get(1), 1);
        obj.put(3, 3);
        assert_eq!(obj.get(2), -1);
        obj.put(4, 4);
        assert_eq!(obj.get(1), -1);
        assert_eq!(obj.get(3), 3);
        assert_eq!(obj.get(4), 4);
    }

    #[test]
    fn t2() {
        let mut obj = LRUCache::new(1);
        obj.put(2, 1);
        assert_eq!(obj.get(2), 1);
        obj.put(3, 2);
        assert_eq!(obj.get(2), -1);
        assert_eq!(obj.get(3), 2);
    }
}
