#![allow(dead_code, non_snake_case)]

// What LeetCode provides implicitly; glob-imported, so a file's own definitions win.
pub mod prelude {
    pub use std::cell::RefCell;
    pub use std::rc::Rc;

    #[derive(Debug, PartialEq, Eq)]
    pub struct TreeNode {
        pub val: i32,
        pub left: Option<Rc<RefCell<TreeNode>>>,
        pub right: Option<Rc<RefCell<TreeNode>>>,
    }

    impl TreeNode {
        #[inline]
        pub fn new(val: i32) -> Self {
            TreeNode { val, left: None, right: None }
        }
    }

    #[derive(PartialEq, Eq, Clone, Debug)]
    pub struct ListNode {
        pub val: i32,
        pub next: Option<Box<ListNode>>,
    }

    impl ListNode {
        #[inline]
        pub fn new(val: i32) -> Self {
            ListNode { next: None, val }
        }
    }
}

include!(concat!(env!("OUT_DIR"), "/mods.rs"));
