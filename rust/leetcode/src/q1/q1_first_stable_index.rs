impl Solution {
    pub fn first_stable_index(nums: Vec<i32>, k: i32) -> i32 {
        let mut aa: Vec<i32> = nums
            .iter()
            .rev()
            .scan(i32::MAX, |aa, &bb| {
                *aa = (*aa).min(bb);
                Some(*aa)
            })
            .collect();
        aa.reverse();
        nums.iter()
            .zip(aa)
            .scan(0, |bb, (&cc, dd)| {
                *bb = (*bb).max(cc);
                Some(*bb - dd <= k)
            })
            .position(|ee| ee)
            .map(|ff| ff as i32)
            .unwrap_or(-1)
    }
}
