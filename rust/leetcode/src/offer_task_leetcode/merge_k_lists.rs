#!/usr/bin/env rust-script

use std::cmp::Ordering;
use std::collections::BinaryHeap;

#[derive(PartialEq, Eq, Clone, Debug)]
pub struct ListNode {
    pub val: i32,
    pub next: Option<Box<ListNode>>,
}

impl ListNode {
    #[inline]
    fn new(val: i32) -> Self {
        ListNode { next: None, val }
    }
}

pub struct Solution;

struct MinNode(Box<ListNode>);

impl PartialEq for MinNode {
    fn eq(&self, other: &Self) -> bool {
        self.0.val == other.0.val
    }
}

impl Eq for MinNode {}

impl PartialOrd for MinNode {
    fn partial_cmp(&self, other: &Self) -> Option<Ordering> {
        Some(self.cmp(other))
    }
}

impl Ord for MinNode {
    fn cmp(&self, other: &Self) -> Ordering {
        other.0.val.cmp(&self.0.val)
    }
}

impl Solution {
    pub fn merge_k_lists(lists: Vec<Option<Box<ListNode>>>) -> Option<Box<ListNode>> {
        let mut heap = BinaryHeap::new();

        for list in lists {
            if let Some(node) = list {
                heap.push(MinNode(node));
            }
        }

        let mut dummy = Box::new(ListNode::new(0));
        let mut current = &mut dummy;

        while let Some(MinNode(mut node)) = heap.pop() {
            if let Some(next) = node.next.take() {
                heap.push(MinNode(next));
            }

            current.next = Some(node);
            current = current.next.as_mut().unwrap();
        }

        dummy.next
    }
}

fn main() {
    println!("Merge k sorted lists example");
    println!(
        "This function works with linked lists - run tests with: cargo test --lib merge_k_lists"
    );
}
