impl Solution {
    pub fn min_moves2(nums: Vec<i32>) -> i32 {
        let mut aa = nums;
        let bb = aa.len() >> 1;
        aa.select_nth_unstable(bb);
        let cc = aa[bb];
        aa.iter().fold(0, |dd, &ee| dd + (ee - cc).abs())
    }
}
