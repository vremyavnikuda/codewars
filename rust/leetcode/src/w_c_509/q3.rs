impl Solution {
    pub fn divisible_game(nums: Vec<i32>) -> i32 {
        const Q0: i64 = 1_000_000_007;
        let q1 = *nums.iter().max().unwrap() as usize;
        let q2 = *nums.iter().min().unwrap() as i64;
        let mut q3 = vec![false; q1 + 2];
        for &a1 in &nums {
            let a1 = a1 as usize;
            let mut a2 = 1usize;
            while a2 * a2 <= a1 {
                if a1 % a2 == 0 {
                    let a3 = a1 / a2;
                    if a2 > 1 {
                        q3[a2] = true;
                    }
                    if a3 > 1 {
                        q3[a3] = true;
                    }
                }
                a2 += 1;
            }
        }
        let mut a4 = 2usize;
        while a4 <= q1 + 1 && q3[a4] {
            a4 += 1;
        }
        let mut q4 = -q2;
        let mut q5 = a4 as i32;
        for a5 in 2..=q1 {
            if q3[a5] {
                let mut a6 = 0i64;
                let mut a7 = i64::MIN;
                for &a8 in &nums {
                    let a9 = if a8 as usize % a5 == 0 {
                        a8 as i64
                    } else {
                        -(a8 as i64)
                    };
                    a6 = if a6 > 0 { a6 + a9 } else { a9 };
                    a7 = a7.max(a6);
                }
                if a7 > q4 || (a7 == q4 && (a5 as i32) < q5) {
                    q4 = a7;
                    q5 = a5 as i32;
                }
            }
        }
        ((((q4 % Q0) * q5 as i64) % Q0 + Q0) % Q0) as i32
    }
}
