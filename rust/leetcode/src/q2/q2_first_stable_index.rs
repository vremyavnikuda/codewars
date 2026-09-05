impl Solution {
    pub fn first_stable_index(nums: Vec<i32>, k: i32) -> i32 {
        let mut aa: Vec<i32> = nums
            .iter()
            .rev()
            .scan(i32::MAX, |bb, &cc| {
                *bb = (*bb).min(cc);
                Some(*bb)
            })
            .collect();
        aa.reverse();
        nums.iter()
            .enumerate()
            .scan(0, |dd, (ee, &ff)| {
                *dd = (*dd).max(ff);
                Some((ee, *dd))
            })
            .find(|&(ee, dd)| dd - aa[ee] <= k)
            .map(|(ee, _)| ee as i32)
            .unwrap_or(-1)
    }
}
