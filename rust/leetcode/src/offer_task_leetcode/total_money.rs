#!/usr/bin/env rust-script

pub struct Solution;
impl Solution {
    pub fn total_money(n: i32) -> i32 {
        let complete_weeks = n / 7;
        let remaining_days = n % 7;
        let first_week_sum = 28;
        let last_week_sum = 28 + 7 * (complete_weeks - 1);
        let total_from_complete_weeks = (first_week_sum + last_week_sum) * complete_weeks / 2;
        let first_day_amount = complete_weeks + 1;
        let last_day_amount = complete_weeks + remaining_days;
        let total_from_remaining_days = (first_day_amount + last_day_amount) * remaining_days / 2;
        total_from_complete_weeks + total_from_remaining_days
    }
}

fn main() {
    let test1 = Solution::total_money(4);
    println!("Test 1: n=4, total = {} (expected 10)", test1);

    let test2 = Solution::total_money(10);
    println!("Test 2: n=10, total = {} (expected 37)", test2);

    let test3 = Solution::total_money(20);
    println!("Test 3: n=20, total = {} (expected 96)", test3);
}
