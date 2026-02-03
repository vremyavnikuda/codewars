#!/usr/bin/env rust-script

// Definition for singly-linked list.
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

use std::collections::HashSet;

impl Solution {
    pub fn modified_list(nums: Vec<i32>, head: Option<Box<ListNode>>) -> Option<Box<ListNode>> {
        let nums_set: HashSet<i32> = nums.into_iter().collect();
        if head.is_none() {
            return None;
        }
        let mut dummy = Box::new(ListNode { val: 0, next: head });
        let mut current = &mut dummy;
        while let Some(ref mut next_node) = current.next {
            if nums_set.contains(&next_node.val) {
                current.next = next_node.next.take();
            } else {
                current = current.next.as_mut().unwrap();
            }
        }
        dummy.next
    }
}

pub struct Solution;

fn main() {
    println!("Modified list example");
    println!(
        "This function works with linked lists - run tests with: cargo test --lib modified_list"
    );
}
