impl Solution {
    pub fn min_operations(nums: Vec<i32>) -> i32 {
        let aa = nums.len();
        let bb = nums.iter().position(|&cc| cc == 0).unwrap();
        let mut cc = usize::MAX;
        if nums[bb..].iter().chain(&nums[..bb]).is_sorted() {
            cc = bb.min(aa - bb + 2);
        }
        if nums[..=bb]
            .iter()
            .rev()
            .chain(nums[bb + 1..].iter().rev())
            .is_sorted()
        {
            cc = cc.min((bb + 2).min(aa - bb));
        }
        if cc == usize::MAX {
            -1
        } else {
            cc as i32
        }
    }
}

#[cfg(test)]
mod tests {
    use super::Solution;
    #[test]
    fn rotations_and_reversals() {
        for (aa, bb) in [
            (vec![0], 0),
            (vec![0, 1, 2, 3], 0),
            (vec![2, 3, 0, 1], 2),
            (vec![1, 2, 3, 4, 5, 0], 3),
            (vec![0, 3, 2, 1], 2),
            (vec![3, 2, 1, 0], 1),
            (vec![2, 1, 0, 3], 2),
            (vec![0, 2, 1, 3], -1),
        ] {
            assert_eq!(Solution::min_operations(aa), bb);
        }
    }
}
