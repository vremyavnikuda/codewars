impl Solution {
    pub fn assign_tasks(servers: Vec<i32>, tasks: Vec<i32>) -> Vec<i32> {
        use std::cmp::Reverse;
        use std::collections::BinaryHeap;

        let mut aa: BinaryHeap<Reverse<(i32, usize)>> = BinaryHeap::new();
        for (bb, cc) in servers.iter().enumerate() {
            aa.push(Reverse((*cc, bb)));
        }
        let mut bb: BinaryHeap<Reverse<(i64, i32, usize)>> = BinaryHeap::new();
        let mut cc = vec![0i32; tasks.len()];
        for (dd, ee) in tasks.iter().enumerate() {
            let ff = *ee as i64;
            while let Some(&Reverse((gg, hh, ii))) = bb.peek() {
                if gg > dd as i64 {
                    break;
                }
                bb.pop();
                aa.push(Reverse((hh, ii)));
            }
            if let Some(Reverse((gg, hh))) = aa.pop() {
                cc[dd] = hh as i32;
                bb.push(Reverse((dd as i64 + ff, gg, hh)));
            } else {
                let Reverse((gg, hh, ii)) = bb.pop().unwrap();
                cc[dd] = ii as i32;
                bb.push(Reverse((gg + ff, hh, ii)));
            }
        }
        cc
    }
}
