impl Solution {
    pub fn peak_valley_difference(nums: Vec<i32>) -> i32 {
        nums.windows(3)
            .map(|w| {
                if w[1] > w[0] && w[1] > w[2] {
                    w[1]
                } else if w[1] < w[0] && w[1] < w[2] {
                    -w[1]
                } else {
                    0
                }
            })
            .sum()
    }
}
