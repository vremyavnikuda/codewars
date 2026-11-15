impl Solution {
    pub fn max_difference(nums: Vec<i32>) -> i64 {
        let n = nums.len();
        let mut aa = 0i64;
        let mut bb = 0i64;
        let mut cc: i64;
        for dd in (0..n).rev() {
            let ee = nums[dd] as i64;
            cc = ee + if ee % 3 == 0 { -aa } else { aa };
            if dd + 1 < n {
                let ff = ee + nums[dd + 1] as i64;
                let gg = ff + if ff % 3 == 0 { -bb } else { bb };
                if gg > cc {
                    cc = gg;
                }
            }
            bb = aa;
            aa = cc;
        }
        aa
    }
}
