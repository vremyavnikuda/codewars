pub struct Solution;

impl Solution {
    pub fn longest_repeating(
        s: String,
        query_characters: String,
        query_indices: Vec<i32>,
    ) -> Vec<i32> {
        fn qa(q1: usize, q2: usize, q3: usize, q4: &[u8], q5: &mut [(i32, i32, i32)]) {
            let q6 = (q2 + q3) >> 1;
            let q7 = q1 << 1;
            let q8 = q7 | 1;
            let q9 = (q6 - q2 + 1) as i32;
            let qb = (q3 - q6) as i32;
            q5[q1].2 = q5[q7].2.max(q5[q8].2);
            q5[q1].0 = q5[q7].0;
            q5[q1].1 = q5[q8].1;
            if q4[q6] == q4[q6 + 1] {
                if q5[q7].0 == q9 {
                    q5[q1].0 += q5[q8].0;
                }
                if q5[q8].1 == qb {
                    q5[q1].1 += q5[q7].1;
                }
                q5[q1].2 = q5[q1].2.max(q5[q7].1 + q5[q8].0);
            }
        }

        fn qb(q1: usize, q2: usize, q3: usize, q4: &[u8], q5: &mut [(i32, i32, i32)]) {
            if q2 != q3 {
                let q6 = (q2 + q3) >> 1;
                qb(q1 << 1, q2, q6, q4, q5);
                qb(q1 << 1 | 1, q6 + 1, q3, q4, q5);
                qa(q1, q2, q3, q4, q5);
            }
        }

        fn qc(
            q1: usize,
            q2: usize,
            q3: usize,
            q4: usize,
            q5: u8,
            q6: &mut [u8],
            q7: &mut [(i32, i32, i32)],
        ) {
            if q2 == q3 {
                q6[q4] = q5;
                return;
            }
            let q8 = (q2 + q3) >> 1;
            if q4 <= q8 {
                qc(q1 << 1, q2, q8, q4, q5, q6, q7);
            } else {
                qc(q1 << 1 | 1, q8 + 1, q3, q4, q5, q6, q7);
            }
            qa(q1, q2, q3, q6, q7);
        }

        let mut a1 = s.into_bytes();
        let a2 = query_characters.as_bytes();
        let a3 = query_indices.len();
        let a4 = a1.len();
        let mut a5 = vec![(1i32, 1i32, 1i32); a4 * 4 + 1];
        qb(1, 0, a4 - 1, &a1, &mut a5);
        let mut a6 = Vec::with_capacity(a3);
        for q1 in 0..a3 {
            qc(
                1,
                0,
                a4 - 1,
                query_indices[q1] as usize,
                a2[q1],
                &mut a1,
                &mut a5,
            );
            a6.push(a5[1].2);
        }
        a6
    }
}
