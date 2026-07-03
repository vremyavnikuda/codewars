use std::cmp::Reverse;
use std::collections::BinaryHeap;

impl Solution {
    pub fn find_max_path_score(edges: Vec<Vec<i32>>, online: Vec<bool>, k: i64) -> i32 {
        let a1 = online.len();
        let mut a2: Vec<Vec<(usize, i32)>> = vec![vec![]; a1];
        let mut a3 = i32::MAX;
        let mut a4 = 0;

        for q1 in &edges {
            let q2 = q1[0] as usize;
            let q3 = q1[1] as usize;
            let q4 = q1[2];
            if !online[q2] || !online[q3] {
                continue;
            }
            a2[q2].push((q3, q4));
            a3 = a3.min(q4);
            a4 = a4.max(q4);
        }

        let a5 = |a6: i32| -> bool {
            let mut q1 = vec![i64::MAX / 4; a1];
            q1[0] = 0;
            let mut q2: BinaryHeap<Reverse<(i64, usize)>> = BinaryHeap::new();
            q2.push(Reverse((0, 0)));
            while let Some(Reverse((q3, q4))) = q2.pop() {
                if q3 > k {
                    return false;
                }
                if q4 == a1 - 1 {
                    return true;
                }
                if q3 > q1[q4] {
                    continue;
                }
                for &(q5, q6) in &a2[q4] {
                    if q6 < a6 {
                        continue;
                    }
                    let q7 = q3 + q6 as i64;
                    if q7 < q1[q5] {
                        q1[q5] = q7;
                        q2.push(Reverse((q7, q5)));
                    }
                }
            }
            false
        };

        while a3 < a4 {
            let a6 = (a3 + a4 + 1) >> 1;
            if a5(a6) {
                a3 = a6;
            } else {
                a4 = a6 - 1;
            }
        }

        if a5(a3) { a3 } else { -1 }
    }
}
