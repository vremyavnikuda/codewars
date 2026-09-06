impl Solution {
    pub fn count_good_rotations(nums: Vec<i32>) -> i32 {
        let aa = nums.len();
        let bb = aa / 2;
        let cc: i64 = nums.iter().map(|&dd| dd as i64).sum();
        let mut ee: i64 = nums[..bb].iter().map(|&dd| dd as i64).sum();
        let mut ff = 0;
        for gg in 0..aa {
            ff += (2 * ee > cc) as i32;
            ee += nums[(gg + bb) % aa] as i64 - nums[gg] as i64;
        }
        ff
    }
}
