impl Solution {
    pub fn count_special_integers(nums: Vec<i32>) -> i32 {
        let mut aa = [0_u8; 101];

        nums.iter()
            .enumerate()
            .filter(|&(bb, cc)| bb == 0 || nums[bb - 1] != *cc)
            .for_each(|(_, &bb)| aa[bb as usize] += 1);

        aa.into_iter().filter(|&bb| bb == 1).count() as i32
    }
}
