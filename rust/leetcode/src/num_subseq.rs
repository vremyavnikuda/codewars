#!/usr/bin/env rust-script

pub struct Solution;

impl Solution {
    pub fn num_subseq(mut nums: Vec<i32>, target: i32) -> i32 {
        nums.sort_unstable();

        const MOD: i64 = 1_000_000_007;
        let q = nums.len();

        let mut q1 = vec![1i64; q + 1];
        for q2 in 1..=q {
            q1[q2] = (q1[q2 - 1] * 2) % MOD;
        }

        let mut q3 = 0i64;

        for q4 in 0..q {
            if nums[q4] * 2 > target {
                break;
            }

            let q5 = target - nums[q4];
            let q6 = match nums[q4 + 1..].binary_search(&q5) {
                Ok(q7) => q4 + 1 + q7,
                Err(q7) => q4 + q7,
            };

            q3 = (q3 + q1[q6 - q4]) % MOD;
        }

        q3 as i32
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_example_1() {
        assert_eq!(Solution::num_subseq(vec![3, 5, 6, 7], 9), 4);
    }

    #[test]
    fn test_example_2() {
        assert_eq!(Solution::num_subseq(vec![3, 3, 6, 8], 10), 6);
    }

    #[test]
    fn test_example_3() {
        assert_eq!(Solution::num_subseq(vec![2, 3, 3, 4, 6, 7], 12), 61);
    }
}

fn main() {
    let nums1 = vec![3, 5, 6, 7];
    let target1 = 9;
    println!("Input: nums = {:?}, target = {}", nums1, target1);
    println!("Result: {}", Solution::num_subseq(nums1, target1));

    let nums2 = vec![3, 3, 6, 8];
    let target2 = 10;
    println!("\nInput: nums = {:?}, target = {}", nums2, target2);
    println!("Result: {}", Solution::num_subseq(nums2, target2));
}
