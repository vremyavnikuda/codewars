impl Solution {
    pub fn target_indices(nums: Vec<i32>, target: i32) -> Vec<i32> {
        let (aa, bb) = nums.iter().fold((0, 0), |(aa, bb), &cc| {
            (
                aa + usize::from(cc < target),
                bb + usize::from(cc == target),
            )
        });
        let mut cc = nums;
        cc.truncate(bb);
        cc.iter_mut()
            .enumerate()
            .for_each(|(dd, ee)| *ee = (aa + dd) as i32);
        cc
    }
}
