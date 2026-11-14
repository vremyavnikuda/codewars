impl Solution {
    pub fn minimum_sum_subarray(nums: Vec<i32>, l: i32, r: i32) -> i32 {
        (0..nums.len())
            .flat_map(|aa| {
                nums[aa..].iter().enumerate().scan(0, |bb, (cc, &dd)| {
                    *bb += dd;
                    Some(((cc + 1) as i32, *bb))
                })
            })
            .filter(|&(ee, asd)| (l..=r).contains(&ee) && asd > 0)
            .map(|(_, ff)| ff)
            .min()
            .unwrap_or(-1)
    }
}
