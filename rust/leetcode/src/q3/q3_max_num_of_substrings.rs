impl Solution {
    pub fn max_num_of_substrings(s: String) -> Vec<String> {
        let aa = s.as_bytes();
        let bb = aa.len();
        let mut cc = [bb; 26];
        let mut dd = [0usize; 26];
        for (ee, &ff) in aa.iter().enumerate() {
            let gg = (ff - b'a') as usize;
            if cc[gg] == bb {
                cc[gg] = ee;
            }
            dd[gg] = ee;
        }
        let mut hh: Vec<String> = Vec::new();
        let mut ii = bb;
        for jj in 0..bb {
            let kk = (aa[jj] - b'a') as usize;
            if jj != cc[kk] {
                continue;
            }
            let mut ll = dd[kk];
            let mut mm = jj + 1;
            while mm <= ll {
                let nn = (aa[mm] - b'a') as usize;
                if cc[nn] < jj {
                    ll = bb;
                    break;
                }
                if dd[nn] > ll {
                    ll = dd[nn];
                }
                mm += 1;
            }
            if ll >= bb {
                continue;
            }
            if ii == bb || jj > ii {
                hh.push(s[jj..=ll].to_string());
            } else if ll < dd[(aa[ii] - b'a') as usize] {
                *hh.last_mut().unwrap() = s[jj..=ll].to_string();
            } else {
                continue;
            }
            ii = ll;
        }
        hh
    }
}
