#!/usr/bin/env rust-script

pub struct Solution;
impl Solution {
    pub fn number_of_beams(bank: Vec<String>) -> i32 {
        let mut total_beams = 0;
        let mut previous_device_count = 0;
        for row in &bank {
            let current_device_count = row.chars().filter(|&c| c == '1').count() as i32;
            if current_device_count > 0 {
                total_beams += previous_device_count * current_device_count;
                previous_device_count = current_device_count;
            }
        }
        total_beams
    }
}

fn main() {
    let bank1 = vec![
        "011001".to_string(),
        "000000".to_string(),
        "010100".to_string(),
        "001000".to_string(),
    ];
    let test1 = Solution::number_of_beams(bank1);
    println!("Test 1: {} (expected 8)", test1);

    let bank2 = vec!["000".to_string(), "111".to_string(), "000".to_string()];
    let test2 = Solution::number_of_beams(bank2);
    println!("Test 2: {} (expected 0)", test2);
}
