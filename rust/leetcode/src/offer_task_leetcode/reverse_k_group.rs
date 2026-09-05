#!/usr/bin/env rust-script

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

impl Solution {
    pub fn reverse_k_group(head: Option<Box<ListNode>>, k: i32) -> Option<Box<ListNode>> {
        let mut q = 0;
        let mut q1 = &head;
        while q1.is_some() && q < k {
            q1 = &q1.as_ref().unwrap().next;
            q += 1;
        }

        if q < k {
            return head;
        }

        let mut q2 = head;
        let mut q3 = None;
        let mut q4 = 0;

        while q4 < k {
            if let Some(mut q5) = q2 {
                q2 = q5.next.take();
                q5.next = q3;
                q3 = Some(q5);
                q4 += 1;
            }
        }

        if let Some(ref mut q6) = q3 {
            let mut q7 = q6;
            while q7.next.is_some() {
                q7 = q7.next.as_mut().unwrap();
            }
            q7.next = Self::reverse_k_group(q2, k);
        }

        q3
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    fn vec_to_list(v: Vec<i32>) -> Option<Box<ListNode>> {
        let mut q = None;
        for &q1 in v.iter().rev() {
            let mut q2 = Box::new(ListNode::new(q1));
            q2.next = q;
            q = Some(q2);
        }
        q
    }

    fn list_to_vec(mut head: Option<Box<ListNode>>) -> Vec<i32> {
        let mut q = Vec::new();
        while let Some(q1) = head {
            q.push(q1.val);
            head = q1.next;
        }
        q
    }

    #[test]
    fn test_example_1() {
        let head = vec_to_list(vec![1, 2, 3, 4, 5]);
        let result = Solution::reverse_k_group(head, 2);
        assert_eq!(list_to_vec(result), vec![2, 1, 4, 3, 5]);
    }

    #[test]
    fn test_example_2() {
        let head = vec_to_list(vec![1, 2, 3, 4, 5]);
        let result = Solution::reverse_k_group(head, 3);
        assert_eq!(list_to_vec(result), vec![3, 2, 1, 4, 5]);
    }
}

fn main() {
    println!("Reverse nodes in k-group");
    println!("Run tests with: cargo test --lib reverse_k_group");
}
