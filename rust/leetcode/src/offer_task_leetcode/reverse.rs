#!/usr/bin/env rust-script

pub struct Solution;

impl Solution {
    pub fn reverse(mut x: i32) -> i32 {
        let mut q = 0i32;
        while x != 0 {
            if q > i32::MAX / 10 || q < i32::MIN / 10 {
                return 0;
            }
            let q1 = x % 10;
            q = q * 10 + q1;
            x /= 10;
        }
        q
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_example_1() {
        assert_eq!(Solution::reverse(123), 321);
    }

    #[test]
    fn test_example_2() {
        assert_eq!(Solution::reverse(-123), -321);
    }

    #[test]
    fn test_example_3() {
        assert_eq!(Solution::reverse(120), 21);
    }

    #[test]
    fn test_overflow() {
        assert_eq!(Solution::reverse(1534236469), 0);
    }
}

fn main() {
    let x1 = 123;
    println!("Input: {}", x1);
    println!("Result: {}", Solution::reverse(x1));

    let x2 = -123;
    println!("\nInput: {}", x2);
    println!("Result: {}", Solution::reverse(x2));

    let x3 = 120;
    println!("\nInput: {}", x3);
    println!("Result: {}", Solution::reverse(x3));
}
