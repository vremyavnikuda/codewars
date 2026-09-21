impl Solution {
    pub fn result_array(nums: Vec<i32>, k: i32) -> Vec<i64> {
        let aa = k as usize;
        let mut bb = vec![0i64; aa];
        let mut cc = vec![0i64; aa];
        let mut dd = vec![0i64; aa];
        for &ee in &nums {
            dd.fill(0);
            let ff = ee as i64;
            for (gg, &hh) in cc.iter().enumerate() {
                if hh != 0 {
                    dd[((gg as i64 * ff) % (k as i64)) as usize] += hh;
                }
            }
            dd[(ff % (k as i64)) as usize] += 1;
            for (ii, jj) in bb.iter_mut().zip(dd.iter()) {
                *ii += jj;
            }
            std::mem::swap(&mut cc, &mut dd);
        }
        bb
    }
}
