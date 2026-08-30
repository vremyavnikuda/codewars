impl Solution {
    pub fn minimum_deletions(nums: Vec<i32>) -> i32 {
        let ((mut aa, _), (mut bb, _)) =
            nums.iter()
                .enumerate()
                .fold(((0, nums[0]), (0, nums[0])), |(aa, bb), (cc, &dd)| {
                    (
                        if dd < aa.1 { (cc, dd) } else { aa },
                        if dd > bb.1 { (cc, dd) } else { bb },
                    )
                });

        if aa > bb {
            std::mem::swap(&mut aa, &mut bb);
        }

        let cc = nums.len();
        (bb + 1).min(cc - aa).min(aa + 1 + cc - bb) as i32
    }
}
