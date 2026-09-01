use std::collections::VecDeque;

pub struct Solution;

impl Solution {
    pub fn min_moves(classroom: Vec<String>, energy: i32) -> i32 {
        let aa = classroom.len();
        let bb = classroom[0].len();
        let asd = classroom
            .iter()
            .map(|cc| cc.chars().filter(|dd| "L".contains(*dd)).count())
            .sum::<usize>();
        if asd == 0 {
            return 0;
        }
        let mut ee = vec![vec![0i32; bb]; aa];
        let mut ff = 0usize;
        let mut gg = 0usize;
        let mut hh = 0usize;
        for (ii, jj) in classroom.iter().enumerate() {
            for (kk, ll) in jj.bytes().enumerate() {
                let mm = ll as char;
                if "S".contains(mm) {
                    gg = ii;
                    hh = kk;
                } else if "L".contains(mm) {
                    ee[ii][kk] = ff as i32;
                    ff += 1;
                }
            }
        }
        let nn = energy as usize;
        let oo = 1usize << asd;
        let pp = aa * bb * (nn + 1) * oo;
        let mut qq = vec![false; pp];
        let rr = |vv: usize, ww: usize, xx: usize, yy: usize| {
            ((vv * bb + ww) * (nn + 1) + xx) * oo + yy
        };
        let mut ss = VecDeque::new();
        let tt = (1usize << asd) - 1;
        qq[rr(gg, hh, nn, tt)] = true;
        ss.push_back((gg, hh, energy, tt as i32));
        let uu = [-1i32, 0, 1, 0, -1];
        let mut vv = 0i32;
        while !ss.is_empty() {
            let ww = ss.len();
            for _ in 0..ww {
                let (xx, yy, zz, ab) = ss.pop_front().unwrap();
                let ab = ab as usize;
                if ab == 0 {
                    return vv;
                }
                if zz <= 0 {
                    continue;
                }
                for ac in 0..4 {
                    let ad = xx as i32 + uu[ac];
                    let ae = yy as i32 + uu[ac + 1];
                    if ad < 0 || ad >= aa as i32 || ae < 0 || ae >= bb as i32 {
                        continue;
                    }
                    let ad = ad as usize;
                    let ae = ae as usize;
                    let af = classroom[ad].as_bytes()[ae] as char;
                    if "X".contains(af) {
                        continue;
                    }
                    let ag = if "R".contains(af) { energy } else { zz - 1 };
                    let mut ah = ab;
                    if "L".contains(af) {
                        ah &= !(1 << ee[ad][ae]);
                    }
                    let ai = ag as usize;
                    if !qq[rr(ad, ae, ai, ah)] {
                        qq[rr(ad, ae, ai, ah)] = true;
                        ss.push_back((ad, ae, ag, ah as i32));
                    }
                }
            }
            vv += 1;
        }
        -1
    }
}
