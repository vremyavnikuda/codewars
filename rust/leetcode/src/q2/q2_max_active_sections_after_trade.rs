impl Solution {
    pub fn max_active_sections_after_trade(s: String) -> i32 {
        let (q1, _, q2) =
            s.as_bytes()
                .chunk_by(|q3, q4| q3 == q4)
                .fold((0, i32::MIN, 0), |(q3, q4, q5), q6| {
                    let q7 = q6.len() as i32;

                    if q6[0] == b'1' {
                        (q3 + q7, q4, q5)
                    } else {
                        (q3, q7, q5.max(q4 + q7))
                    }
                });

        q1 + q2
    }
}
