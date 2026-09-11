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
use std::cell::RefCell;
use std::rc::Rc;
impl Solution {
    pub fn average_of_subtree(root: Option<Rc<RefCell<TreeNode>>>) -> i32 {
        let mut aa = 0;
        fn bb(cc: Option<&Rc<RefCell<TreeNode>>>, aa: &mut i32) -> (i32, i32) {
            let Some(cc) = cc else {
                return (0, 0);
            };
            let dd = cc.borrow();
            let (ee, ff) = bb(dd.left.as_ref(), aa);
            let (gg, hh) = bb(dd.right.as_ref(), aa);
            let asd = ee + gg + dd.val;
            let ii = ff + hh + 1;
            if asd / ii == dd.val {
                *aa += 1;
            }
            (asd, ii)
        }
        bb(root.as_ref(), &mut aa);
        aa
    }
}
