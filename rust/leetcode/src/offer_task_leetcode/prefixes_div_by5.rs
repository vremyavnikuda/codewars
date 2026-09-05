#!/usr/bin/env rust-script

pub struct Solution;

impl Solution {
    pub fn prefixes_div_by5(nums: Vec<i32>) -> Vec<bool> {
        let mut q = Vec::new();
        let mut q1 = 0;

        for q2 in nums {
            q1 = ((q1 << 1) | q2) % 5;
            q.push(q1 == 0);
        }

        q
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_example_1() {
        assert_eq!(
            Solution::prefixes_div_by5(vec![0, 1, 1]),
            vec![true, false, false]
        );
    }

    #[test]
    fn test_example_2() {
        assert_eq!(
            Solution::prefixes_div_by5(vec![1, 1, 1]),
            vec![false, false, false]
        );
    }

    #[test]
    fn test_example_3() {
        assert_eq!(
            Solution::prefixes_div_by5(vec![0, 1, 1, 1, 1, 1]),
            vec![true, false, false, false, true, false]
        );
    }
}

fn main() {
    let nums1 = vec![0, 1, 1];
    println!("Input: {:?}", nums1);
    println!("Result: {:?}", Solution::prefixes_div_by5(nums1));

    let nums2 = vec![1, 1, 1];
    println!("\nInput: {:?}", nums2);
    println!("Result: {:?}", Solution::prefixes_div_by5(nums2));

    let nums3 = vec![0, 1, 1, 1, 1, 1];
    println!("\nInput: {:?}", nums3);
    println!("Result: {:?}", Solution::prefixes_div_by5(nums3));
}
