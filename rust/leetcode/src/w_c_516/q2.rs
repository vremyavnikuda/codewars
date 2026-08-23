impl Solution {
    pub fn find_disappeared_numbers(nums: Vec<i32>, lower: i32, upper: i32) -> Vec<Vec<i32>> {
        let mut aa = [false; 100_001];
        nums.into_iter().for_each(|bb| aa[bb as usize] = true);
        let mut bb = Vec::new();
        let mut cc = lower;
        for dd in lower..=upper {
            if aa[dd as usize] {
                if cc < dd {
                    bb.push(vec![cc, dd - 1]);
                }
                cc = dd + 1;
            }
        }
        if cc <= upper {
            bb.push(vec![cc, upper]);
        }
        bb
    }
}

#[cfg(test)]
mod aa {
    use super::*;

    #[test]
    fn bb() {
        assert_eq!(
            Solution::find_disappeared_numbers(vec![3, 9, 7], 1, 12),
            vec![vec![1, 2], vec![4, 6], vec![8, 8], vec![10, 12]]
        );
        assert_eq!(
            Solution::find_disappeared_numbers(vec![1, 1], 5, 7),
            vec![vec![5, 7]]
        );
        assert_eq!(
            Solution::find_disappeared_numbers(vec![2, 3, 5], 2, 3),
            Vec::<Vec<i32>>::new()
        );
        assert_eq!(
            Solution::find_disappeared_numbers(vec![1, 3, 5], 2, 4),
            vec![vec![2, 2], vec![4, 4]]
        );
    }
}
