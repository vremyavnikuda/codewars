#!/usr/bin/env rust-script

pub struct Solution;

impl Solution {
    pub fn max_sum_div_three(nums: Vec<i32>) -> i32 {
        let q = nums.len();
        let q1 = i32::MIN / 2;
        let mut q2 = vec![vec![0; 3]; q + 1];

        q2[0][0] = 0;
        q2[0][1] = q1;
        q2[0][2] = q1;

        for q3 in 1..=q {
            let q4 = nums[q3 - 1];

            for q5 in 0..3 {
                let q6 = q2[q3 - 1][q5];
                let q7 = ((q5 as i32 - q4 % 3 + 3) % 3) as usize;
                let q8 = q2[q3 - 1][q7] + q4;

                q2[q3][q5] = q6.max(q8);
            }
        }

        q2[q][0]
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_example_1() {
        assert_eq!(Solution::max_sum_div_three(vec![3, 6, 5, 1, 8]), 18);
    }

    #[test]
    fn test_example_2() {
        assert_eq!(Solution::max_sum_div_three(vec![4]), 0);
    }

    #[test]
    fn test_example_3() {
        assert_eq!(Solution::max_sum_div_three(vec![1, 2, 3, 4, 4]), 12);
    }
}

fn main() {
    let nums1 = vec![3, 6, 5, 1, 8];
    println!("Input: {:?}", nums1);
    println!("Result: {}", Solution::max_sum_div_three(nums1));

    let nums2 = vec![4];
    println!("\nInput: {:?}", nums2);
    println!("Result: {}", Solution::max_sum_div_three(nums2));

    let nums3 = vec![1, 2, 3, 4, 4];
    println!("\nInput: {:?}", nums3);
    println!("Result: {}", Solution::max_sum_div_three(nums3));
}
