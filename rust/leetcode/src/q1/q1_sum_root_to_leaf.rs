// Definition for a binary tree node.
// #[derive(Debug, PartialEq, Eq)]
// pub struct TreeNode {
//   pub val: i32,
//   pub left: Option<Rc<RefCell<TreeNode>>>,
//   pub right: Option<Rc<RefCell<TreeNode>>>,
// }
// 
// impl TreeNode {
//   #[inline]
//   pub fn new(val: i32) -> Self {
//     TreeNode {
//       val,
//       left: None,
//       right: None
//     }
//   }
// }
use std::rc::Rc;
use std::cell::RefCell;
pub struct Solution;
impl Solution {
    #[inline(always)]
    pub fn sum_root_to_leaf(root: Option<Rc<RefCell<TreeNode>>>) -> i32 {
        #[inline(always)]
        fn _0(root: Option<&Rc<RefCell<TreeNode>>>, t: i32) -> i32 {
            let Some(root) = root else { return 0 };
            let _1 = root.borrow();
            let _2 = (t << 1) | (_1.val & 1);
            match (_1.left.as_ref(), _1.right.as_ref()) {
                (None, None) => _2,
                (_3, _4) => _0(_3, _2) + _0(_4, _2),
            }
        }
        _0(root.as_ref(), 0)
    }
}
