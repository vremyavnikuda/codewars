use std::cmp::Reverse;
use std::collections::{BTreeSet, BinaryHeap};

impl Solution {
    pub fn busiest_servers(k: i32, arrival: Vec<i32>, load: Vec<i32>) -> Vec<i32> {
        let mut aa: BTreeSet<i32> = (0..k).collect();
        let mut bb = BinaryHeap::new();
        let mut cc = vec![0; k as usize];
        for dd in 0..arrival.len() {
            let ee = arrival[dd];
            let ff = ee + load[dd];
            loop {
                match bb.peek() {
                    Some(&Reverse((gg, hh))) if gg <= ee => {
                        bb.pop();
                        aa.insert(hh);
                    }
                    _ => break,
                }
            }
            if aa.is_empty() {
                continue;
            }
            let ii = dd as i32 % k;
            let jj = match aa.range(ii..).next() {
                Some(&kk) => kk,
                None => *aa.iter().next().unwrap(),
            };
            cc[jj as usize] += 1;
            bb.push(Reverse((ff, jj)));
            aa.remove(&jj);
        }
        let ll = *cc.iter().max().unwrap();
        (0..k).filter(|&mm| cc[mm as usize] == ll).collect()
    }
}
