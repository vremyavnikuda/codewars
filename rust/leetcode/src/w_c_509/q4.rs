impl Solution {
    pub fn get_sum(nums: Vec<i32>) -> i64 {
        let q1 = nums.len();
        let q2 = 2 * q1 + 1;
        let mut q3 = vec![0i64; q1 + 1];
        for (a1, &a2) in nums.iter().enumerate() {
            q3[a1 + 1] = q3[a1] + a2 as i64;
        }
        let q4 = |a1: i32| -> i32 {
            if a1 < 0 {
                return i32::MIN;
            }
            if a1 as usize >= q2 {
                return i32::MIN + 1;
            }
            if a1 % 2 == 0 {
                -1
            } else {
                nums[((a1 - 1) / 2) as usize]
            }
        };
        let mut q5 = vec![0i32; q2];
        let mut q6 = 0i32;
        let mut q7 = 0i32;
        let mut q8 = 0i64;
        for a1 in 0..q2 {
            let a2 = a1 as i32;
            let mut a3 = if a2 < q7 {
                (q7 - a2).min(q5[(2 * q6 - a2) as usize])
            } else {
                0
            };
            while q4(a2 - a3 - 1) == q4(a2 + a3 + 1) {
                a3 += 1;
            }
            q5[a1] = a3;
            if a2 + a3 > q7 {
                q6 = a2;
                q7 = a2 + a3;
            }
            let a4 = (a2 - a3) / 2;
            let a5 = (a2 + a3) / 2;
            let a6 = q3[a5 as usize] - q3[a4 as usize];
            if a6 > q8 {
                q8 = a6;
            }
        }
        q8
    }
}
