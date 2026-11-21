impl Solution {
    pub fn find_subtree_sizes(parent: Vec<i32>, s: String) -> Vec<i32> {
        let aa = s.len();
        let mut bb = vec![vec![]; aa];
        for (cc, &dd) in parent.iter().enumerate().skip(1) {
            bb[dd as usize].push(cc);
        }
        let ee = s.as_bytes();
        let mut ff = vec![0; aa];
        let mut gg: [Vec<usize>; 26] = Default::default();
        fn hh(
            ii: usize,
            jj: i32,
            bb: &[Vec<usize>],
            ee: &[u8],
            ff: &mut [i32],
            gg: &mut [Vec<usize>; 26],
        ) {
            ff[ii] = 1;
            let kk = (ee[ii] - b'a') as usize;
            gg[kk].push(ii);
            for &ll in &bb[ii] {
                hh(ll, ii as i32, bb, ee, ff, gg);
            }
            let mm = if gg[kk].len() > 1 {
                gg[kk][gg[kk].len() - 2] as i32
            } else {
                jj
            };
            if mm >= 0 {
                ff[mm as usize] += ff[ii];
            }
            gg[kk].pop();
        }
        hh(0, -1, &bb, ee, &mut ff, &mut gg);
        ff
    }
}
