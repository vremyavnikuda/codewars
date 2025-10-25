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
