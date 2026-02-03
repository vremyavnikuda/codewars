#!/usr/bin/env rust-script

pub struct Solution;
impl Solution {
    pub fn int_to_roman(num: i32) -> String {
        let roman_symbols = [
            "M", "CM", "D", "CD", "C", "XC", "L", "XL", "X", "IX", "V", "IV", "I",
        ];
        let values = [1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1];
        let mut result = String::new();
        let mut num = num;
        for i in 0..roman_symbols.len() {
            while num >= values[i] {
                num -= values[i];
                result.push_str(roman_symbols[i]);
            }
        }
        result
    }
}

fn main() {
    println!("=== Integer to Roman ===\n");

    let test1 = Solution::int_to_roman(3);
    println!("Test 1: 3 = {}", test1);

    let test2 = Solution::int_to_roman(58);
    println!("Test 2: 58 = {}", test2);

    let test3 = Solution::int_to_roman(1994);
    println!("Test 3: 1994 = {}", test3);
}
