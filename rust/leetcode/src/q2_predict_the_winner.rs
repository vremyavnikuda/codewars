struct Solution;

impl Solution {
    pub fn predict_the_winner(nums: Vec<i32>) -> bool {
        let _0 = nums.len();
        let mut _1 = vec![0i32; _0 + 1];
        for _2 in 1..=_0 {
            for _3 in 0..=_0 - _2 {
                _1[_3] = std::cmp::max(nums[_3] - _1[_3 + 1], nums[_3 + _2 - 1] - _1[_3]);
            }
        }
        _1[0] >= 0
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn t1() {
        assert_eq!(Solution::predict_the_winner(vec![1, 5, 2]), false);
    }

    #[test]
    fn t2() {
        assert_eq!(Solution::predict_the_winner(vec![1, 5, 233, 7]), true);
    }

    #[test]
    fn t3() {
        assert_eq!(Solution::predict_the_winner(vec![1]), true);
    }

    #[test]
    fn t4() {
        assert_eq!(Solution::predict_the_winner(vec![0, 0, 0, 0, 0, 0]), true);
    }
}
