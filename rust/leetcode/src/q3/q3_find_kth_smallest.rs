impl Solution {
    pub fn find_kth_smallest(coins: Vec<i32>, k: i32) -> i64 {
        let q1 = |q2: i64| -> i64 {
            (1u32..(1u32 << coins.len())).fold(0i64, |q3, q4| {
                match coins.iter().enumerate().try_fold(1i64, |a1, (a2, &a3)| {
                    if (q4 >> a2) & 1 == 1 {
                        let (mut a4, mut a5) = (a1, i64::from(a3));
                        while a5 != 0 {
                            let a6 = a4 % a5;
                            a4 = a5;
                            a5 = a6;
                        }
                        let a7 = a1 / a4 * i64::from(a3);
                        (a7 <= q2).then_some(a7)
                    } else {
                        Some(a1)
                    }
                }) {
                    Some(a4) if q4.count_ones() & 1 == 1 => q3 + q2 / a4,
                    Some(a4) => q3 - q2 / a4,
                    None => q3,
                }
            })
        };
        let (mut q5, mut q6, mut a5) = (1i64, 100_000_000_000i64, -1i64);
        while q5 <= q6 {
            let a6 = q5 + (q6 - q5) / 2;
            if q1(a6) >= i64::from(k) {
                a5 = a6;
                q6 = a6 - 1;
            } else {
                q5 = a6 + 1;
            }
        }
        a5
    }
}
