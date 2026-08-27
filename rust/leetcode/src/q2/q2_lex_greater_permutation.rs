impl Solution {
    pub fn lex_greater_permutation(s: String, target: String) -> String {
        let mut aa = s.into_bytes();
        let bb = target.as_bytes();
        let mut cc = [0usize; 26];
        for &dd in &aa {
            cc[(dd - b'a') as usize] += 1;
        }
        let mut dd = 0;
        while dd < bb.len() {
            let ee = (bb[dd] - b'a') as usize;
            if cc[ee] == 0 {
                break;
            }
            aa[dd] = bb[dd];
            cc[ee] -= 1;
            dd += 1;
        }
        loop {
            if dd < bb.len() {
                let ee = (bb[dd] - b'a') as usize + 1;
                if let Some(ff) = (ee..26).find(|&gg| cc[gg] > 0) {
                    aa[dd] = b'a' + ff as u8;
                    cc[ff] -= 1;
                    let mut ee = dd + 1;
                    for (ff, &gg) in cc.iter().enumerate() {
                        for _ in 0..gg {
                            aa[ee] = b'a' + ff as u8;
                            ee += 1;
                        }
                    }
                    return String::from_utf8(aa).unwrap();
                }
            }
            if dd == 0 {
                return String::new();
            }
            dd -= 1;
            cc[(bb[dd] - b'a') as usize] += 1;
        }
    }
}
