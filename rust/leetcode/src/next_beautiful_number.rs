#!/usr/bin/env rust-script

pub struct Solution;
impl Solution {
    pub fn next_beautiful_number(n: i32) -> i32 {
        let mut candidate = n + 1;
        loop {
            let mut digit_frequency = [0; 10];
            let mut temp = candidate;
            while temp > 0 {
                let digit = temp % 10;
                digit_frequency[digit as usize] += 1;
                temp /= 10;
            }
            let mut is_beautiful = true;
            temp = candidate;
            while temp > 0 {
                let digit = temp % 10;
                if digit != digit_frequency[digit as usize] {
                    is_beautiful = false;
                    break;
                }
                temp /= 10;
            }
            if is_beautiful {
                return candidate;
            }
            candidate += 1;
        }
    }
}


fn main() {
    let test1 = Solution::next_beautiful_number(1);
    println!("Test 1: n=1 => {} (next beautiful number)", test1);
    
    let test2 = Solution::next_beautiful_number(1000);
    println!("Test 2: n=1000 => {} (next beautiful number)", test2);
    
    let test3 = Solution::next_beautiful_number(3000);
    println!("Test 3: n=3000 => {} (next beautiful number)", test3);
}
