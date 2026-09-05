#!/usr/bin/env rust-script

pub struct Solution;
impl Solution {
    pub fn convert(s: String, num_rows: i32) -> String {
        if num_rows == 1 {
            return s;
        }
        let mut rows: Vec<String> = vec![String::new(); num_rows as usize];
        let mut i = 0;
        let mut k = -1;
        let bytes = s.as_bytes();
        for &c in bytes {
            rows[i].push(c as char);
            if i == 0 || i == (num_rows - 1) as usize {
                k = -k;
            }
            i = (i as i32 + k) as usize;
        }
        let mut result = String::new();
        for row in rows {
            result.push_str(&row);
        }
        result
    }
}

fn main() {
    let s = "PAYPALISHIRING".to_string();
    let num_rows = 3;
    println!("Input: s = {}, numRows = {}", s, num_rows);
    println!("Result: {}", Solution::convert(s, num_rows));

    let s2 = "PAYPALISHIRING".to_string();
    let num_rows2 = 4;
    println!("\nInput: s = {}, numRows = {}", s2, num_rows2);
    println!("Result: {}", Solution::convert(s2, num_rows2));
}
