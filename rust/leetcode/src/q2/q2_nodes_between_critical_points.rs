// Definition for singly-linked list.
// #[derive(PartialEq, Eq, Clone, Debug)]
// pub struct ListNode {
//   pub val: i32,
//   pub next: Option<Box<ListNode>>
// }
//
// impl ListNode {
//   #[inline]
//   fn new(val: i32) -> Self {
//     ListNode {
//       next: None,
//       val
//     }
//   }
// }
impl Solution {
    pub fn nodes_between_critical_points(head: Option<Box<ListNode>>) -> Vec<i32> {
        let mut aa =
            std::iter::successors(head.as_deref(), |bb| bb.next.as_deref()).map(|bb| bb.val);
        let (Some(mut bb), Some(mut cc)) = (aa.next(), aa.next()) else {
            return vec![-1, -1];
        };
        let mut dd = -1;
        let mut ee = -1;
        let mut asd = i32::MAX;
        for (ff, gg) in aa.enumerate() {
            let ff = ff as i32;
            if cc < bb.min(gg) || cc > bb.max(gg) {
                if dd != -1 {
                    asd = asd.min(ff - ee);
                } else {
                    dd = ff;
                }
                ee = ff;
            }
            bb = cc;
            cc = gg;
        }
        if dd == ee {
            vec![-1, -1]
        } else {
            vec![asd, ee - dd]
        }
    }
}
