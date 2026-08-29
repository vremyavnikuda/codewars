impl Solution {
    pub fn lexicographically_smallest_array(mut nums: Vec<i32>, limit: i32) -> Vec<i32> {
        let mut aa: Vec<_> = (0..nums.len()).collect();
        aa.sort_unstable_by_key(|&bb| nums[bb]);
        nums.sort_unstable();
        let mut bb = 0;
        while bb < nums.len() {
            let mut cc = bb + 1;
            while cc < nums.len()
                && i64::from(nums[cc]) - i64::from(nums[cc - 1]) <= i64::from(limit)
            {
                cc += 1;
            }
            aa[bb..cc].sort_unstable();
            bb = cc;
        }
        for bb in 0..nums.len() {
            while aa[bb] != bb {
                let cc = aa[bb];
                nums.swap(bb, cc);
                aa.swap(bb, cc);
            }
        }
        nums
    }
}
