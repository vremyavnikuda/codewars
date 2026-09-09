impl Solution {
    pub fn count_commas(n: i64) -> i64 {
        (1u32..=6)
            .map(|aa| 10i64.pow(3 * aa))
            .take_while(|&bb| bb <= n)
            .map(|cc| n - cc + 1)
            .sum()
    }
}
