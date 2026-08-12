use std::collections::HashMap;

pub struct Solution;

impl Solution {
    pub fn max_subarray_length(nums: Vec<i32>, k: i32) -> i32 {
        let k = k as usize;
        let mut cnt: HashMap<i32, usize> = HashMap::new();
        let mut l = 0usize;
        let mut ans = 0usize;
        for (r, &x) in nums.iter().enumerate() {
            *cnt.entry(x).or_insert(0) += 1;
            while cnt[&x] > k {
                cnt.entry(nums[l]).and_modify(|c| *c -= 1);
                l += 1;
            }
            ans = ans.max(r - l + 1);
        }
        ans as i32
    }
}

#[cfg(test)]
mod tests {
    use super::Solution;

    #[test]
    fn t1() {
        assert_eq!(Solution::max_subarray_length(vec![1, 2, 3, 1, 2, 3, 1, 2], 2), 6);
    }

    #[test]
    fn t2() {
        assert_eq!(Solution::max_subarray_length(vec![1, 2, 1, 2, 3], 2), 5);
    }

    #[test]
    fn t3() {
        assert_eq!(Solution::max_subarray_length(vec![2, 2, 2, 2, 3, 3], 1), 2);
    }

    #[test]
    fn t4() {
        assert_eq!(Solution::max_subarray_length(vec![1], 1), 1);
    }

    #[test]
    fn t5() {
        assert_eq!(Solution::max_subarray_length(vec![1, 1, 1, 1], 3), 3);
    }

    #[test]
    fn t6() {
        assert_eq!(Solution::max_subarray_length(vec![1, 2, 1, 2, 1], 1), 2);
    }
}
