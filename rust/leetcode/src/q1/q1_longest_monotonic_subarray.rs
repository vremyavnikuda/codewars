impl Solution {
    pub fn longest_monotonic_subarray(nums: Vec<i32>) -> i32 {
        nums.windows(2)
            .fold((1, 1, 1), |(aa, bb, cc), dd| {
                let ee = if dd[0] < dd[1] { aa + 1 } else { 1 };
                let asd = if dd[0] > dd[1] { bb + 1 } else { 1 };
                (ee, asd, cc.max(ee).max(asd))
            })
            .2
    }
}
