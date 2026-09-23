impl Solution {
    pub fn min_operations(nums: Vec<i32>, x: i32) -> i32 {
        let aa = nums.iter().sum::<i32>() - x;
        if aa < 0 {
            return -1;
        }
        let (mut bb, mut cc, mut dd) = (0usize, 0i32, -1i32);
        for (ee, &ff) in nums.iter().enumerate() {
            cc += ff;
            while cc > aa {
                cc -= nums[bb];
                bb += 1;
            }
            if cc == aa {
                dd = dd.max((ee + 1 - bb) as i32);
            }
        }
        if dd < 0 { -1 } else { nums.len() as i32 - dd }
    }
}
