impl Solution {
    pub fn largest_integer(nums: Vec<i32>, k: i32) -> i32 {
        let q1 = nums.len();
        if k == 1 {
            let mut q2 = nums;
            q2.sort_unstable();

            return q2
                .iter()
                .enumerate()
                .filter_map(|(q3, q4)| {
                    ((q3 == 0 || q2[q3 - 1] != *q4) && (q3 + 1 == q1 || q2[q3 + 1] != *q4))
                        .then_some(*q4)
                })
                .max()
                .unwrap_or(-1);
        }
        if k == q1 as i32 {
            return nums.iter().copied().max().unwrap_or(-1);
        }
        let q2 = |q3: usize| {
            if nums[..q3].contains(&nums[q3]) || nums[q3 + 1..].contains(&nums[q3]) {
                -1
            } else {
                nums[q3]
            }
        };
        q2(0).max(q2(q1 - 1))
    }
}
