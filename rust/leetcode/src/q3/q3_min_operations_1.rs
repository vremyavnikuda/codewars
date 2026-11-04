use std::collections::BTreeMap;

struct Aa {
    aa: BTreeMap<i32, i32>,
    bb: BTreeMap<i32, i32>,
    cc: usize,
    dd: usize,
    ee: i64,
    ff: i64,
}

impl Aa {
    fn new() -> Self {
        Self {
            aa: BTreeMap::new(),
            bb: BTreeMap::new(),
            cc: 0,
            dd: 0,
            ee: 0,
            ff: 0,
        }
    }

    fn gg(&mut self, aa: bool, bb: i32) {
        let (cc, dd, ee) = if aa {
            (&mut self.aa, &mut self.cc, &mut self.ee)
        } else {
            (&mut self.bb, &mut self.dd, &mut self.ff)
        };
        *cc.entry(bb).or_insert(0) += 1;
        *dd += 1;
        *ee += bb as i64;
    }

    fn hh(&mut self, aa: bool, bb: i32) {
        let (cc, dd, ee) = if aa {
            (&mut self.aa, &mut self.cc, &mut self.ee)
        } else {
            (&mut self.bb, &mut self.dd, &mut self.ff)
        };
        let ff = cc.get_mut(&bb).unwrap();
        *ff -= 1;
        if *ff == 0 {
            cc.remove(&bb);
        }
        *dd -= 1;
        *ee -= bb as i64;
    }

    fn asd(&mut self) {
        while self.cc as i64 - self.dd as i64 > 1 {
            let aa = *self.aa.keys().next_back().unwrap();
            self.hh(true, aa);
            self.gg(false, aa);
        }
        while self.dd > self.cc {
            let aa = *self.bb.keys().next().unwrap();
            self.hh(false, aa);
            self.gg(true, aa);
        }
    }

    fn ii(&mut self, aa: i32) {
        self.gg(false, aa);
        let bb = *self.bb.keys().next().unwrap();
        self.hh(false, bb);
        self.gg(true, bb);
        self.asd();
    }

    fn jj(&mut self, aa: i32) {
        if self.aa.contains_key(&aa) {
            self.hh(true, aa);
        } else {
            self.hh(false, aa);
        }
        self.asd();
    }

    fn kk(&self) -> i64 {
        let aa = *self.aa.keys().next_back().unwrap() as i64;
        self.cc as i64 * aa - self.ee + self.ff - self.dd as i64 * aa
    }
}

impl Solution {
    pub fn min_operations(nums: Vec<i32>, x: i32, k: i32) -> i64 {
        let aa = nums.len();
        let bb = x as usize;
        let cc = k as usize;
        let dd = i64::MAX / 4;
        let mut ee = vec![vec![dd; cc + 1]; aa + 1];
        ee[0][0] = 0;
        let mut ff = Aa::new();
        for gg in 1..=aa {
            ff.ii(nums[gg - 1]);
            let hh = ff.kk();
            for ii in 0..=cc {
                ee[gg][ii] = ee[gg - 1][ii];
                if ii > 0 && gg >= bb {
                    ee[gg][ii] = ee[gg][ii].min(ee[gg - bb][ii - 1] + hh);
                }
            }
            if gg >= bb {
                ff.jj(nums[gg - bb]);
            }
        }
        ee[aa][cc]
    }
}
