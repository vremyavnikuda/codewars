#!/usr/bin/env rust-script

pub struct Solution;
impl Solution {
    pub fn min_cost(colors: String, needed_time: Vec<i32>) -> i32 {
        let mut a = 0;
        let qwe = colors.len();
        let dd: Vec<char> = colors.chars().collect();
        let mut a1 = 0;
        while a1 < qwe {
            let mut w3 = a1;
            let mut b2 = 0;
            let mut c4 = 0;
            while w3 < qwe && dd[w3] == dd[a1] {
                b2 += needed_time[w3];
                c4 = c4.max(needed_time[w3]);
                w3 += 1;
            }
            if w3 - a1 > 1 {
                a += b2 - c4;
            }
            a1 = w3;
        }
        a
    }
}

fn main() {
    let colors = "abaac".to_string();
    let needed_time = vec![1, 2, 3, 4, 5];
    println!("Input: colors = {}, neededTime = {:?}", colors, needed_time);
    println!("Result: {}", Solution::min_cost(colors, needed_time));
}
