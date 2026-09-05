#!/usr/bin/env rust-script

pub struct Solution;
impl Solution {
    pub fn smallest_number(n: i32) -> i32 {
        let mut n2 = 1;
        while n2 - 1 < n {
            n2 <<= 1;
        }
        n2 - 1
    }
}

fn main() {
    let test1 = Solution::smallest_number(5);
    println!("Test 1: n=5 => {} (expected 7)", test1);

    let test2 = Solution::smallest_number(10);
    println!("Test 2: n=10 => {} (expected 15)", test2);

    let test3 = Solution::smallest_number(3);
    println!("Test 3: n=3 => {} (expected 3)", test3);
}
