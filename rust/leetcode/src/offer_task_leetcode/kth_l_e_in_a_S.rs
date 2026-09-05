use std::cmp::Reverse;
use std::collections::BinaryHeap;

struct KthLargest {
    k: usize,
    h: BinaryHeap<Reverse<i32>>,
}

impl KthLargest {
    fn new(k: i32, nums: Vec<i32>) -> Self {
        let mut obj = KthLargest {
            k: k as usize,
            h: BinaryHeap::new(),
        };

        for n in nums {
            obj.add(n);
        }

        obj
    }

    fn add(&mut self, val: i32) -> i32 {
        self.h.push(Reverse(val));

        if self.h.len() > self.k {
            self.h.pop();
        }

        self.h.peek().unwrap().0
    }
}

fn main() {
    let mut obj = KthLargest::new(3, vec![4, 5, 8, 2]);
    println!("add(3): {}", obj.add(3));
    println!("add(5): {}", obj.add(5));
    println!("add(10): {}", obj.add(10));
    println!("add(9): {}", obj.add(9));
    println!("add(4): {}", obj.add(4));
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn t1() {
        let mut obj = KthLargest::new(3, vec![4, 5, 8, 2]);
        assert_eq!(obj.add(3), 4);
        assert_eq!(obj.add(5), 5);
        assert_eq!(obj.add(10), 5);
        assert_eq!(obj.add(9), 8);
        assert_eq!(obj.add(4), 8);
    }

    #[test]
    fn t2() {
        let mut obj = KthLargest::new(1, vec![]);
        assert_eq!(obj.add(-3), -3);
        assert_eq!(obj.add(-2), -2);
        assert_eq!(obj.add(-4), -2);
        assert_eq!(obj.add(0), 0);
        assert_eq!(obj.add(4), 4);
    }

    #[test]
    fn t3() {
        let mut obj = KthLargest::new(2, vec![0]);
        assert_eq!(obj.add(-1), -1);
        assert_eq!(obj.add(1), 0);
        assert_eq!(obj.add(-2), 0);
        assert_eq!(obj.add(-4), 0);
        assert_eq!(obj.add(3), 1);
    }
}
