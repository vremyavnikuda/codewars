impl Solution {
    pub fn max_digit_range(nums: Vec<i32>) -> i32 {
        let q1 = |mut a1: i32| -> i32 {
            let mut a2 = 0;
            let mut a3 = 9;
            while a1 > 0 {
                let a4 = a1 % 10;
                a2 = a2.max(a4);
                a3 = a3.min(a4);
                a1 /= 10;
            }
            a2 - a3
        };
        let q2 = nums.iter().map(|&q3| q1(q3)).max().unwrap();
        nums.iter().filter(|&&q3| q1(q3) == q2).sum()
    }
}
