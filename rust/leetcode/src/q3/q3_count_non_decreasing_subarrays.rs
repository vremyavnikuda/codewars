impl Solution {
    pub fn count_non_decreasing_subarrays(nums: Vec<i32>, k: i32) -> i64 {
        let mut aa: i64 = 0;
        let mut bb: i64 = 0;
        let mut cc: std::collections::VecDeque<(i32, i32)> = std::collections::VecDeque::new();
        let mut dd: i64 = nums.len() as i64 - 1;
        let mut ee: i64 = dd;
        while dd >= 0 {
            let ff = nums[dd as usize];
            let mut gg: i32 = 1;
            while let Some(&(hh, ii)) = cc.back().filter(|&&(hh, _)| hh < ff) {
                cc.pop_back();
                gg += ii;
                bb += (ff - hh) as i64 * ii as i64;
            }
            cc.push_back((ff, gg));
            while bb > k as i64 {
                let &(jj, kk) = cc.front().unwrap();
                cc.pop_front();
                bb -= (jj - nums[ee as usize]) as i64;
                ee -= 1;
                if kk > 1 {
                    cc.push_front((jj, kk - 1));
                }
            }
            aa += ee - dd + 1;
            dd -= 1;
        }
        aa
    }
}
