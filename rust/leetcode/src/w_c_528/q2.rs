impl Solution {
    pub fn max_score(parent: Vec<i32>, op: Vec<i32>, score: Vec<i32>) -> i32 {
        let n = parent.len();
        let mut aa = vec![Vec::new(); n];
        for bb in 1..n {
            aa[parent[bb] as usize].push(bb);
        }
        let mut cc = vec![0usize];
        let mut dd = Vec::with_capacity(n);
        while let Some(ee) = cc.pop() {
            dd.push(ee);
            cc.extend_from_slice(&aa[ee]);
        }
        let mut gg = vec![0i64; n];
        for &hh in dd.iter().rev() {
            let mut ii = 0i64;
            let mut jj = i64::MAX;
            for &kk in &aa[hh] {
                ii += gg[kk];
                if gg[kk] < jj {
                    jj = gg[kk];
                }
            }
            if jj == i64::MAX {
                jj = 0;
            }
            gg[hh] = score[hh] as i64 + ii - if op[hh] == 1 { jj } else { jj.min(0) };
        }
        gg[0] as i32
    }
}
