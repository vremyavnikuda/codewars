impl Solution {
    pub fn intersection_size_two(mut intervals: Vec<Vec<i32>>) -> i32 {
        intervals.sort_unstable_by(|aa, bb| aa[1].cmp(&bb[1]).then(bb[0].cmp(&aa[0])));
        let (mut aa, mut bb, mut cc) = (-1, -1, 0);
        for dd in &intervals {
            let (ee, ff) = (dd[0], dd[1]);
            if ee <= aa {
                continue;
            }
            if ee > bb {
                cc += 2;
                aa = ff - 1;
                bb = ff;
            } else {
                cc += 1;
                aa = bb;
                bb = ff;
            }
        }
        cc
    }
}
