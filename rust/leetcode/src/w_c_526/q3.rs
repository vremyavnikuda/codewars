impl Solution {
    pub fn min_operations(nums: Vec<i32>, locked: Vec<i32>, k: i32) -> i32 {
        let n = nums.len();
        let mut max = 0;
        let mut unlocks = 0;
        for i in 0..n {
            max = max.max(nums[i]);
            if locked[i] == 1 && !(nums[i] == i as i32 + 1 && max == i as i32 + 1) {
                unlocks += 1;
            }
        }
        if unlocks > k {
            return -1;
        }
        let inversions = (0..n)
            .map(|i| (i + 1..n).filter(|&j| nums[i] > nums[j]).count() as i32)
            .sum::<i32>();
        unlocks + inversions
    }
}

#[cfg(test)]
mod tests {
    use super::*;
    #[test]
    fn examples() {
        assert_eq!(
            Solution::min_operations(vec![2, 1, 3, 4], vec![0, 1, 0, 1], 1),
            2
        );
        assert_eq!(Solution::min_operations(vec![3, 1, 2], vec![1, 0, 1], 2), 4);
        assert_eq!(
            Solution::min_operations(vec![2, 3, 1], vec![1, 0, 0], 0),
            -1
        );
    }
}
